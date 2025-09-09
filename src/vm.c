#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STACK_MAX 256

enum {
    OP_PUSH   = 0x01,
    OP_ADD    = 0x02,
    OP_SUB    = 0x03,
    OP_MUL    = 0x04,
    OP_DIV    = 0x05,
    OP_PRINT  = 0x06,
    OP_HALT   = 0x07
};

typedef struct {
    int32_t stack[STACK_MAX];
    int sp; 
} VM;

static void push(VM *vm, int32_t val){ 
    if(vm->sp >= STACK_MAX) {
        fprintf(stderr, "Stack overflow!\n");
        exit(1);

    }
    vm->stack[vm->sp++] = val;
}

static int32_t pop(VM *vm) {
    if (vm->sp <= 0) {
        fprintf(stderr, "Stack underflow!\n");
        exit(1);
    }
    return vm->stack[ --vm->sp];
}

static int32_t read_int32_le(FILE *f) {
    uint8_t buf[4];
    if(fread(buf, 1, 4, f) != 4){
        fprintf(stderr, "Unexpected EOF while reading int32\n");
        exit(1);
    }
    return (int32_t)(buf[0] | (buf[1]<<8) | (buf[2]<<16) | (buf[3]<<24));
}

int main(int argc, char **argv){
    if (argc < 2) {
        fprintf(stderr, "Usage: %s program.bc\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("fopen");
        return 1;
    }

    VM vm = { .sp = 0};

    while (1) {
        int c = fgetc(f);
        if (c == EOF) {
            fprintf(stderr, "Unexpected EOF while reading opcode\n");
            break;
        }

        uint8_t opcode = (uint8_t)c;

        switch (opcode) {
            case OP_PUSH: {
                int32_t val = read_int32_le(f);
                push(&vm, val);
                break;
            }
            case OP_ADD : {
                int32_t b = pop(&vm);
                int32_t a = pop(&vm);
                push(&vm, a + b);
                break;
            }
            case OP_SUB: {
                int32_t b = pop(&vm);
                int32_t a = pop(&vm);
                push(&vm, a - b);
                break;
            }
            case  OP_MUL: {
                int32_t b = pop(&vm);
                int32_t a = pop(&vm);
                push(&vm, a * b);
                break;
            }
            case OP_DIV: {
                int32_t b = pop(&vm);
                int32_t a = pop(&vm);
                if (b == 0){ 
                    fprintf(stderr, "Division by zero!\n");
                    exit(1);
                }
                push(&vm, a / b);
                break;
            }
            case OP_PRINT: {
                int32_t v = pop(&vm);
                printf("%d\n", v);
                break;
            }
            case OP_HALT: 
                fclose(f);
                return 0;
            default:
                fprintf(stderr, "invalid opcode: 0x%02X\n", opcode);
                fclose(f);
                return 1;
        }
      
    }
    
    fclose(f);
    return 0;
}

