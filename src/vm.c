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
}:

typedef struct {
    int32_t stack[STACK_MAX];
    int sp; 
} VM;

static void push(VM *vm, int32_t val){
    if(vm->sp >= STACK_MAX) {
        fprint(stderr, "Stack overflow!\n");
        exit(1);

    }
    vm->stack[vm->sp++] = val;
}

static int32_t (VM *vm) {
    if (vm->sp <=0){
        fprintf(stderr, "Stack underflow!\n");
        exit(1);
    }
    return vm->stack[ --vm->sp]
}

static() {
    if(){

    }
    return
}

int main(int argc, char **argv){
    if(){
        return
    }

    FILE *f:
    if(){
        return 1;
    }

    VM vm = { .sp = 0};

    while (condition){
        if(){

        }

        uint8_t 

        switch (expression){
            case : {
                int32_t

                break;
            }
            case : {
                int32_t
                int32_t

                break;
            }
            case : {
                int32_t
                int32_t

                break;
            }
            case : {
                int32_t
                int32_t

                break;
            }
            case : {
                int32_t
                int32_t

                break;
            }
            case : {
                int32_t
                int32_t

                break;
            }
            case : 
                fclose(f);
                return 0;
            default:
                fprint(std)
                fclose(f);
                return 1;
        

        }
      
    }
    
    fclose(f);
    return 0;
}

