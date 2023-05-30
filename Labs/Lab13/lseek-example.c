#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int file = open("existingfile.txt", O_RDWR);
    if (file == -1) {
        perror("open");
        return 1;
    }

    // Read existing content from the file
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_size;

    while ((read_size = getline(&buffer, &buffer_size, fdopen(file, "r"))) != -1) {
        // Do nothing, read and discard existing content
    }

    // Add input to the beginning of the file
    printf("Enter text to add at the beginning of the file: ");
    char input[100];
    fgets(input, sizeof(input), stdin);

    lseek(file, 0, SEEK_SET);
    size_t input_length = strlen(input);
    write(file, input, input_length);
    write(file, buffer, read_size);

    // Add input to the end of the file
    printf("Enter text to add at the end of the file: ");
    fgets(input, sizeof(input), stdin);

    lseek(file, 0, SEEK_END);
    write(file, input, strlen(input));

    // Clean up
    free(buffer);
    close(file);

    return 0;
}
