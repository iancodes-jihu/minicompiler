#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s input.src output.bc\n", argv[0]);
        return 1;
    }

    FILE *out = fopen(argv[2], "wb");
    if (!out) return 1;

    fputc(0x01, out); int32_t v=1; fwrite(&v, 4, 1, out);
    fputc(0x01, out); v=2; fwrite(&v, 4, 1, out);
    fputc(0x01, out); v=3; fwrite(&v, 4, 1, out);
    fputc(0x04, out);
    fputc(0x02, out);
    fputc(0x06, out);
    fputc(0x07, out);

    fclose(out);
    return 0;
}