#include "PerfSpB_Error.h"
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>

void PerfSpB_error(char *errorMsg);

void handler(int sig);

void PerfSpB_error(char *errorMsg)
{
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "\033[31m[ FATAL ERROR ] \033[0m:: %s", errorMsg);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    // fprintf(stderr, "\033[31m[ FATAL ERROR ] \033[0m:: %s", errorMsg);
    exit(-1);
}

void handler(int sig)
{
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

void PerfSpB_Error(char *errorMsg, char *filename, const int line)
{
    fprintf(stderr, "\033[31m[ FATAL ERROR ] \033[0m%s at %s:%d\n", errorMsg, filename, line);
    exit(-1);
}