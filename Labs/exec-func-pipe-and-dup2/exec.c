/*
The exec family of functions in Unix-like operating systems allows a process to
replace its current running program with a new program. The functions you
mentioned are part of this family and have different use cases depending on the
arguments and how they handle the environment and the path to the executable.
 */

// =================================================================================

//  execl

int execl(const char *path, const char *arg, ...);

/*
Usage:
    Use execl when you know the exact path of the executable and want to specify
    the command-line arguments directly in the function call.
Arguments:
    path: The full path to the executable.
    arg: The first argument should be the name of the executable (conventionally),
    followed by a variable number of arguments ending with a NULL pointer.
*/

//  Example:
//  execl("/bin/ls", "ls", "-l", "-a", (char *)NULL);


// =================================================================================

int execlp(const char *file, const char *arg, ...);

/*
Usage:
    Use execlp when you want to search for the executable in the directories listed
    in the PATH environment variable.
Arguments:
    file: The name of the executable (without needing the full path).
    arg: The first argument should be the name of the executable (conventionally),
    followed by a variable number of arguments ending with a NULL pointer.
*/

//  Example:
//  execlp("ls", "ls", "-l", "-a", (char *)NULL);


// =================================================================================

int execv(const char *path, char *const argv[]);

/*
Usage:
    Use execv when you know the exact path of the executable and want to pass the
    command-line arguments as an array.
Arguments:
    path: The full path to the executable.
    argv[]: An array of argument strings, with the first argument being the name
    of the executable (conventionally), ending with a NULL pointer.
*/

//  Example:
//  char *args[] = {"ls", "-l", "-a", NULL};
//  execv("/bin/ls", args);

// =================================================================================

int execvp(const char *file, char *const argv[]);


/*
Usage:
    Use execvp when you want to search for the executable in the directories listed
    in the PATH environment variable and want to pass the command-line arguments as an array.
Arguments:
    file: The name of the executable (without needing the full path).
    argv[]: An array of argument strings, with the first argument being the name
    of the executable (conventionally), ending with a NULL pointer.
*/

//  Example:
//  char *args[] = {"ls", "-l", "-a", NULL};
//  execvp("ls", args);
