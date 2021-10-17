#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "message_handler.h"

const char* error_msgs[] = {"Init Error [%d]: %s\n",
               "Error [%d]: %s\n",
               "Quit Error [%d]: %s\n",
               "SDL2 Error [%d]: %s\n",
               "OpenGL Error [%d]: %s\n"};


void h_error_msg(char* msg, int code)
{
    static int i = 0;
    i++;
    fprintf(stderr, error_msgs[code], i , msg);
    exit(EXIT_FAILURE);
}

void h_log_msg(char* msg)
{
    static int i = 0;
    i++;
    fprintf(stdout, "Log [%d]: %s", i , msg);

}

void h_debug_msg(char* msg)
{
    static int i = 0;
    i++;
    fprintf(stdout, "Debug [%d]: %s", i , msg);
}
