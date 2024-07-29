#include <stdio.h>
#include <signal.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h> 
int val =10;
void handler(int sig){val += 5;}

int main(void){
    pid_t pid;

    /*
    When a child process terminates (either normally or abnormally),
    the operating system sends the SIGCHLD signal to the parent process
    to notify it about the termination of its child process. The parent
    process can then handle this signal and take appropriate action,
    such as cleaning up resources associated with the terminated child
    process or spawning new child processes.
    */
    signal(SIGCHLD, handler);
    if ((pid=fork())==0){
        val -= 3;
        exit(0);
    }
    waitpid(pid, NULL,0);
    printf("val = %d\n", val);
    exit(0);
}

/*
1. SIGHUP (Hangup): This signal is typically sent to a process when its controlling terminal is closed or the controlling process terminates.
2. SIGTRAP (Trace Trap): This signal is used by debuggers to intercept and handle certain conditions, such as a breakpoint being hit.
3. SIGKILL (Kill): This signal immediately terminates the process. It cannot be caught or ignored by the process.
4. SIGPIPE (Broken Pipe): This signal is generated when a process attempts to write to a pipe or socket that has been closed on the other end.
5. SIGCHLD (Child Status Changed): This signal is sent to the parent process when a child process terminates, pauses, or resumes.
6. SIGTTIN (Terminal Input for Background Process): This signal is sent to a background process that attempts to read from its controlling terminal.
7. SIGXFSZ (File Size Limit Exceeded): This signal is generated when a process attempts to write to a file and exceeds the file size limit.
8. SIGIO (I/O Input/Output): This signal is sent to a process when asynchronous I/O events occur on a file descriptor.
9. SIGINT (Interrupt): This signal is typically sent by pressing Ctrl+C. It requests the process to terminate gracefully.
10. SIGABRT (Abort): This signal is sent by the abort() function to terminate the process due to a critical error.
11. SIGUSR1 (User-defined Signal 1) and SIGUSR2 (User-defined Signal 2): These signals can be used by applications to implement custom functionality.
12. SIGALRM (Alarm Clock): This signal is sent when a timer set by the alarm() function expires.
13. SIGCONT (Continue): This signal is used to resume a process that has been stopped (e.g., by SIGSTOP).
14. SIGTTOU (Terminal Output for Background Process): This signal is sent to a background process that attempts to write to its controlling terminal.
15. SIGVTALRM (Virtual Timer Alarm): This signal is similar to SIGALRM but is used for a different type of timer.
16. SIGPWR (Power Fail): This signal is generated when the system's power supply is failing.
17. SIGQUIT (Quit): This signal is typically sent by pressing Ctrl+\ and requests the process to terminate with a core dump.
18. SIGBUS (Bus Error): This signal is sent to a process when it performs an invalid memory access on hardware.
19. SIGSEGV (Segmentation Fault): This signal is sent to a process when it attempts to access memory that it doesn't have permission to access.
20. SIGTERM (Termination): This signal requests the process to terminate gracefully. It can be caught or ignored.
21. SIGSTOP (Stop): This signal immediately stops the process. It cannot be caught or ignored.
22. SIGURG (Urgent Data Available): This signal is sent to a process when urgent data is available on a socket.
23. SIGPROF (Profiling Timer Alarm): This signal is sent when the profiling timer set by setitimer() expires.
24. SIGSYS (Bad System Call): This signal is sent to a process when it makes a system call with an invalid number.
25. SIGILL (Illegal Instruction): This signal is sent to a process when it attempts to execute an illegal or undefined instruction.
26. SIGFPE (Floating Point Exception): This signal is sent to a process when it performs an illegal arithmetic operation, such as division by zero or an overflow.
27. SIGSTKFLT (Stack Fault): This signal is sent when a coprocessor stack overflow or underflow occurs.
28. SIGTSTP (Terminal Stop Signal): This signal is typically sent by pressing Ctrl+Z and requests the process to stop.
29. SIGXCPU (CPU Time Limit Exceeded): This signal is generated when a process exceeds its CPU time limit.
30. SIGWINCH (Window Size Change): This signal is sent to a process when the terminal window size changes.
 */
