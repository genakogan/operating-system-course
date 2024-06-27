#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h> // Include for close function
#include <fcntl.h>  // Include for open function


int main() {
    int fd1, fd2, fd3;

    fd1 = open("file1.txt", O_RDONLY);
    if (fd1 == -1) {
        perror("Failed to open file1.txt");
        return 1;
    }
    
    close(fd1);
    fd2 = socket(AF_INET, SOCK_STREAM, 0);
    if (fd2 == -1) {
        perror("Failed to create socket");
        return 1;
    }
   
    fd3 = open("file2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd3 == -1) {
        perror("Failed to create file2.txt");
        return 1;
    }

    printf("fd1 = %d, fd2 = %d, fd3 = %d\n", fd1, fd2, fd3);

    //close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
