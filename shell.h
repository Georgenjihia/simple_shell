#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/*for read/write buffers*/
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR     	1
#define CMD_AND 	2
#define CMD_CHAIN	3
/* for convert number () */
#define CONVERT_LOWERCASE 	1
#define CONVERT_UNSIGNED	2
/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE 	" .simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr -singly linled list
 * @num: the number field
 * @str: a string 
 * @next: points to next node
 * */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
/**
 * struct passinfo - contains pseudo-arguments to pass into a function
 * 	allowing unifrm prototype for function pointer struct
 * @arg: a strig generated from getline containing arguments 
 * @argv: an array of strings generatd from arg
 * @path : a string path for cental command 
 * @argc: the argument count
 *@line_count: the error code count
 * @err_num: the error code for exit ()
 *@linecount_flaf: if on count this line of input
 *@frame: the program filename
 *@env : linled list local copy environ
 *environ:custom modified copy of environ from ll env
 *@history : the history mode
 *@alias: the alias node
 *@env_changed;on if environ was changed 
 *@status: the return status of the last exec'd command

 *
 *
 *
 *
 *
 *
