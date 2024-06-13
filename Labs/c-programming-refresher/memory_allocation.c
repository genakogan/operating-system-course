#include <stdio.h>
#include <stdlib.h>  // for malloc, calloc, realloc
#include <string.h>

int one_dimensional_array_int(){
    int n = 5;
    int *arr1D;

    // Dynamically allocate memory for an integer array of size n using malloc
    arr1D = (int *)malloc(n * sizeof(int));
    if (arr1D == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize array elements
    for (int i = 0; i < n; i++) {
        arr1D[i] = i + 1;
    }

    // Print array elements
    printf("1D Array elements:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr1D[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    free(arr1D);
    return 0;
}

int two_dimensional_array_int(){
    int rows = 3, cols = 4;
    int **arr2D;

    // Dynamically allocate memory for a 2D array of size rows x cols using malloc
    arr2D = (int **)malloc(rows * sizeof(int *));
    if (arr2D == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        arr2D[i] = (int *)malloc(cols * sizeof(int));
        if (arr2D[i] == NULL) {
            printf("Memory allocation failed\n");
            // Free previously allocated memory before returning
            for (int j = 0; j < i; j++) {
                free(arr2D[j]);
            }
            free(arr2D);
            return 1;
        }
    }

    // Initialize array elements
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr2D[i][j] = i * cols + j + 1;
        }
    }

    // Print array elements
    printf("2D Array elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr2D[i][j]);
        }
        printf("\n");
    }

    // Free dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        free(arr2D[i]);
    }
    free(arr2D);

    return 0;
}


int one_dimensional_array_char() {
    int num_chars;
    printf("Enter the number of characters: ");
    scanf("%d", &num_chars);

    // Clear input buffer
    while (getchar() != '\n');

    // Allocate memory for character array (+1 for null terminator)
    char *char_array = (char *)malloc((num_chars + 1) * sizeof(char));
    if (char_array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Input characters
    printf("Enter %d characters: ", num_chars);
    fgets(char_array, num_chars + 1, stdin);

    // Remove newline character if present
    if (char_array[strlen(char_array)] == '\n') {
        printf("strlen(char_array) %lu\n",strlen(char_array));
        char_array[strlen(char_array) - 1] = '\0';
    }

    // Print characters
    printf("1D Array of characters: %s\n", char_array);

    // Compare with another string
    char compare_string[] = "Hello"; // Example string to compare
    if (strcmp(char_array, compare_string) == 0) {
        printf("The entered string matches \"%s\"\n", compare_string);
    } else {
        printf("The entered string does not match \"%s\"\n", compare_string);
    }

    // Free memory
    free(char_array);
    return 0;
}


int two_dimensional_array_char(){
    int num_strings;
    printf("Enter the number of strings: ");
    scanf("%d", &num_strings);

    // Allocate memory for array of strings
    char **str_array = (char **)malloc(num_strings * sizeof(char *));
    if (str_array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Input strings
    char buffer[100]; // assuming max length of each string is 100 characters
    for (int i = 0; i < num_strings; i++) {
        printf("Enter string %d: ", i + 1);
        scanf("%s", buffer);
        str_array[i] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (str_array[i] == NULL) {
            printf("Memory allocation failed\n");
            // Free any already allocated memory before returning
            for (int j = 0; j < i; j++) {
                free(str_array[j]);
            }
            free(str_array);
            return 1;
        }
        strcpy(str_array[i], buffer);
    }

    // Print strings
    printf("1D Array of strings:\n");
    for (int i = 0; i < num_strings; i++) {
        printf("%s\n", str_array[i]);
    }

    // Free memory
    for (int i = 0; i < num_strings; i++) {
        free(str_array[i]);
    }
    free(str_array);

    return 0;
}

void end_of_string(){

    char str[] = "Hello, World!";
    int i = 0;

    // Iterate through the string until we reach the null terminator
    while (str[i] != '\0') {
        printf("Character at index %d: %c\n", i, str[i]);
        i++;
    }

    printf("End of the string reached at index %d\n", i);

}

//int realloc_example(){
//    int *arr;
//    int initial_size = 5;
//    int new_size = 10;
//    int i;
//
//    // Allocating initial memory
//    arr = (int *)malloc(initial_size * sizeof(int));
//    if (arr == NULL) {
//        fprintf(stderr, "Initial malloc failed\n");
//        return 1;
//    }
//
//    // Initializing the array
//    for (i = 0; i < initial_size; i++) {
//        arr[i] = i + 1;
//    }
//
//    printf("Initial array: ");
//    for (i = 0; i < initial_size; i++) {
//        printf("%d ", arr[i]);
//    }
//    printf("\n");
//
//    // Reallocating memory
//    int *temp = (int *)realloc(arr, new_size * sizeof(int));
//    if (temp == NULL) {
//        fprintf(stderr, "Realloc failed\n");
//        free(arr); // Free the original memory block to avoid memory leak
//        return 1;
//    }
//    arr = temp;
//
//    // Initializing the new elements
//    for (i = initial_size; i < new_size; i++) {
//        arr[i] = i + 1;
//    }
//
//    printf("Resized array: ");
//    for (i = 0; i < new_size; i++) {
//        printf("%d ", arr[i]);
//    }
//    printf("\n");
//
//    // Freeing memory
//    free(arr);
//
//    return 0;
//}
int main() {
//    one_dimensional_array_int();
//    two_dimensional_array_int();
//    two_dimensional_array_char();
    one_dimensional_array_char();
//    end_of_string();
    return 0;
}
