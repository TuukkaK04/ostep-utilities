#include <stdio.h>
#include <stdlib.h>

void zip(FILE *fp) {
    int current, next;
    int count = 1;

    current = fgetc(fp);
    if (current == EOF)
        return;

    while ((next = fgetc(fp)) != EOF) {
        if (next == current) {
            count++;
        } else {
            fwrite(&count, sizeof(int), 1, stdout);
            fwrite(&current, sizeof(char), 1, stdout);
            current = next;
            count = 1;
        }
    }
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&current, sizeof(char), 1, stdout);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "my-zip: cannot open file\n");
            exit(1);
        }
        zip(fp);
        fclose(fp);
    }
    return 0;
}
