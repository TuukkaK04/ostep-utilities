#include <stdio.h>
#include <stdlib.h>

void unzip(FILE *fp) {
    int count;
    char ch;

    while (fread(&count, sizeof(int), 1, fp) == 1 &&
           fread(&ch, sizeof(char), 1, fp) == 1) {
        for (int i = 0; i < count; i++)
            printf("%c", ch);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            fprintf(stderr, "my-unzip: cannot open file\n");
            exit(1);
        }
        unzip(fp);
        fclose(fp);
    }
    return 0;
}
