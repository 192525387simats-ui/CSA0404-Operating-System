
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *source, *destination;
    char ch;

    source = fopen("source.txt", "r");

    if (source == NULL) {
        printf("Error: Cannot open source.txt\n");
        printf("Create source.txt in the program folder first.\n");
        return 1;
    }

    destination = fopen("destination.txt", "w");

    if (destination == NULL) {
        printf("Error: Cannot create destination.txt\n");
        fclose(source);
        return 1;
    }

    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
    }

    printf("File copied successfully!\n");

    fclose(source);
    fclose(destination);

    return 0;
}

