#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> // for fork 
#include <wait.h> //for wait
#include <stdlib.h> // for exit
#include<fcntl.h> 

//======================================

void example1(){
	int i, stat;
	pid_t pid[5];
	for(i=0;i<5; i++){
	
		if (0 == (pid[i] = fork())){
			sleep(1);
			exit(100+i);
		}
	}
	
	for(i=0;i<5; i++){
		pid_t cpid = waitpid(pid[i],&stat,0);
		if(WIFEXITED(stat))
			printf("Child %d terminated with status %d\n", cpid, WEXITSTATUS(stat));
	
	}
}

//======================================

void example2(){
	
	if (execlp("ls","ls", "-l",NULL) == -1){
		printf("Error");	
	}
		
}

//======================================

void example3(int argc, char *argv[]){
	/*[ "./t","/bin/ls" ,"-l"]*/
	char *program = argv[1];
	// Starting from argc[1], we pass all the argiments to the program 
	char **args = &argv[1];
	args[argc -1] = NULL; 
	if(execv(program, args)==-1){
		perror("execv");
		exit(EXIT_FAILURE);
	}
	printf("This won't be printed is execv succeeds\n");
}

//======================================

void example4(){

	char *argv[] = { "sh", "-c", "gcc -o tree.o tree.c; ./tree.o", NULL };
	execvp(argv[0], argv);

}

//======================================

void example5(){
		
	 execl("/bin/ls","ls", "-l", NULL); // 1
	 //execlp("ls","ls", "-l", NULL); // 2

	 //char *args[] = {"ls", "-l", NULL};
	 //execv("bin/ls",args); // 3
	 //execvp("ls",args); // 4
}

//======================================


int example6() {
    pid_t pid;
    int myPipeFD[2];
    int ret;
    char buf[40];
    
    ret = pipe(myPipeFD);
    
    if (ret == -1) {
        perror("pipe error");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        printf("child process\n");
        
        // Close reading end of the pipe in the child
        // Resource Management, Signaling End of Data, Preventing Deadlocks
        close(myPipeFD[0]); 
        
        // Write to the pipe
        write(myPipeFD[1], "hello, is there someone?\n", 26);
        
        // Close writing end of the pipe in the child 
        close(myPipeFD[1]); 
        
        // Exit the child process
        exit(0); 
    } else {
        printf("parent process\n");
        
        // Close writing end of the pipe in the parent
        close(myPipeFD[1]); 
        
        // Read from the pipe
        read(myPipeFD[0], buf, sizeof(buf)); 
        printf("I read the message from the buffer: %s\n", buf);
        
        // Close reading end of the pipe in the parent
        close(myPipeFD[0]); 
        
        // Wait for the child process to finish
        wait(NULL); 
    }
    return 0;
}


//======================================

int example7(){

	// We use two pipes
	// First pipe to send input string from parent
	// Second pipe to send concatenated string from child

	int fd1[2]; // Used to store two ends of first pipe
	int fd2[2]; // Used to store two ends of second pipe

	char fixed_str[] = "forgeeks.org";
	char input_str[100];
	pid_t p;

	if (pipe(fd1) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}
	if (pipe(fd2) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}

	scanf("%s", input_str);
	p = fork();

	if (p < 0) {
		fprintf(stderr, "fork Failed");
		return 1;
	}

	// Parent process
	else if (p > 0) {
		char concat_str[100];

		close(fd1[0]); // Close reading end of first pipe

		// Write input string and close writing end of first
		// pipe.
		write(fd1[1], input_str, strlen(input_str) + 1);
		close(fd1[1]);

		// Wait for child to send a string
		wait(NULL);

		close(fd2[1]); // Close writing end of second pipe

		// Read string from child, print it and close
		// reading end.
		read(fd2[0], concat_str, 100);
		printf("Concatenated string %s\n", concat_str);
		close(fd2[0]);
	}

	// child process
	else {
		close(fd1[1]); // Close writing end of first pipe

		// Read a string using first pipe
		char concat_str[100];
		read(fd1[0], concat_str, 100);

		// Concatenate a fixed string with it
		int k = strlen(concat_str);
		int i;
		for (i = 0; i < strlen(fixed_str); i++)
			concat_str[k++] = fixed_str[i];

		concat_str[k] = '\0'; // string ends with '\0'

		// Close both reading ends
		close(fd1[0]);
		close(fd2[0]);

		// Write concatenated string and close writing end
		write(fd2[1], concat_str, strlen(concat_str) + 1);
		close(fd2[1]);

		exit(0);
	}
    return 0;
}

//======================================


#define READ 0
#define WRITE 1

int example8(){

    int p[2];

    if (pipe(p) == -1) {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    pid_t num = fork();

    if (num == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    }

    if (num == 0) {

        close(p[READ]);
        dup2(p[WRITE], STDOUT_FILENO);
        close(p[WRITE]);

        execlp("ls", "ls", "-l", NULL);

        perror("execlp");
        exit(EXIT_FAILURE);
    } else {

        close(p[WRITE]);
        dup2(p[READ], STDIN_FILENO);
        close(p[READ]);


        execlp("sort", "sort", "-r", NULL);

        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;

}

//======================================

int example9()
{ 
    int file_desc = open("dup2.txt",O_WRONLY | O_APPEND); 
      
    // here the newfd is the file descriptor of stdout (i.e. 1) 
    // standart input (stdin): File descriptor 0
    //    // standart output (stdout): File descriptor 1
    // standart Error (stderr): File descriptor 2
    dup2(file_desc, 1) ;  
          
    // All the printf statements will be written in the file 
    // "dup2.txt"
    printf("I will be printed in the file tricky.txt\n"); 
      
return 0; 
}

//======================================

int example10(){

    int fd;
    pid_t pid;

    // Open a file "output.txt" for writing (create if not exist, truncate if exist)
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process

        // Redirect the file descriptor 1 (stdout) to fd
        if (dup2(fd, 1) == -1) {
            perror("dup2 failed");
            exit(EXIT_FAILURE);
        }

        // Close the original file descriptor fd
        close(fd);

        // Execute a command whose output will be redirected to "output.txt"
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");  // execlp will only return on error
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        // Wait for the child to finish
        wait(NULL);

        // Close the file descriptor in the parent
        close(fd);

        printf("Parent process continues...\n");
    }

    return 0;
}

//======================================

#define READ 0
#define WRITE 1

int example11(){

    // Open a file
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    // Duplicate file descriptor to use the opened file descriptor
    int new_fd = dup2(fd, 100); // Duplicate fd to a custom file descriptor (100)
    if (new_fd == -1) {
        perror("dup2");
        return 1;
    }

    // Now the custom file descriptor (100) will point to 'output.txt'

    // Write to the custom file descriptor
    dprintf(100, "This will be written to the file 'output.txt'.\n");

    // Close the original file descriptor
    close(fd);

    return 0;
	
} 

//======================================

int main(int argc, char *argv[]){
	
	// lab2
	//example1();
	//example2();
	//example3(argc, argv);
	
	// exec
	//example4();
	//example5();
	
	//pipe
	//example6();
	//example7();
    //example8();

	//dup
	//example9();
	//example10();
    //example11();
	return 0;
	
}
