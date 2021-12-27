#ifndef MESSAGE_HANDLER_H_INCLUDED
#define MESSAGE_HANDLER_H_INCLUDED

#define print_i(i) printf("# INT:    %s = %d\n", #i, i)
#define print_f(f) printf("# FLOAT:  %s = %f\n", #f, f)
#define print_d(d) printf("# DOUBLE: %s = %f\n", #d, d)
#define print_i_m(i, msg) printf("# INT:   %s \t # %s = %d #  \n", msg, #i, i)
#define print_f_m(f, msg) printf("# FLOAT: %s \t # %s = %f #  \n", msg, #f, f)

#define print_2i(a, b) printf("# INT:   %s = %d\n", #a, a);\
                       printf("# INT:   %s = %d\n", #b, b)

//#define print_char(i, msg) printf("%s \t # %s = %d\n", msg, #i, i)
enum Errors {INIT_ERROR, DEFAULT_ERROR, QUIT_ERROR, SDL_ERROR, OPENGL_ERROR, LOAD_ERROR};


void h_error_msg(char* msg, int code);

void h_log_msg(char* msg);
void h_log_msg_arg(char* msg, char* arg);

void h_debug_msg(char* msg);

void h_func_not_implemented(char* msg);


#endif // MESSAGE_HANDLER_H_INCLUDED
