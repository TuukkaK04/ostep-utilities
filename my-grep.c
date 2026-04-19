#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(const char *term, FILE *fp) {
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1)
        if (strstr(line, term) != NULL)
            printf("%s", line);
    free(line);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    }

    if (argc == 2) {
        grep(argv[1], stdin);
        return 0;
    }

    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "my-grep: cannot open file\n");
            exit(1);
        }
        grep(argv[1], fp);
        fclose(fp);
    }
    return 0;
}
