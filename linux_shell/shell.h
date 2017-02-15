#ifndef SHELL_H
#define SHELL_H
#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
class shell
{
	public:
		void exec(char *argv[]);
		std::string hostname();
		void PIPE(char *argv[],int size,int all);
		void redirection(char *argv[],int size,int all);
};
#endif
