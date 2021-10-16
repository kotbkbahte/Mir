#ifndef MESSAGE_HANDLER_H_INCLUDED
#define MESSAGE_HANDLER_H_INCLUDED


enum Errors {INIT_ERROR, ERROR, QUIT_ERROR, SDL_ERROR, OPENGL_ERROR};


void h_error_msg(char* msg, int code);

void h_log_msg(char* msg);

void h_debug_msg(char* msg);


#endif // MESSAGE_HANDLER_H_INCLUDED
