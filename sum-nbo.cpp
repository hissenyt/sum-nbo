#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    uint32_t total = 0;

    if (argc < 2) {
        fprintf(stderr, "syntax : sum-nbo <file1> [<file2>...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            fprintf(stderr, "Error: cannot open file %s\n", argv[i]);
            return 1;
        }

        uint32_t nbo;
        if (fread(&nbo, sizeof(uint32_t), 1, fp) != 1) {
            fprintf(stderr, "Error: file %s is smaller than 4 bytes\n", argv[i]);
            fclose(fp);
            return 1;
        }

        fclose(fp);

        uint32_t host = ntohl(nbo);

        if (i > 1) {
            printf(" + ");
        }

        printf("%u(0x%08x)", host, host);
        total += host;
    }

    printf(" = %u(0x%08x)\n", total, total);
    return 0;
}
