#include"shell.h"
#include<string>
#include<cstring>
#include<ctime>
#include<sys/stat.h>
#include<fcntl.h>
using namespace std;
string shell::hostname()
{
	char dir[100];
	getcwd(dir,sizeof(dir));
	string usr = " @ Andy's shell $ ";
	string str(dir);
	str.append(usr);
	return str;
}
void shell::exec(char *argv[])
{
	//special case for "cd"
	if(strcmp(argv[0],"cd")==0)
	{
		chdir(argv[1]);
		return;
	}
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		cout<<"fork error";
		exit(-1);
	}
	//execvp(char *path,char *argv[])
	else if(pid == 0)
	{
		if(execvp(argv[0],argv)==-1)
		{
			cout<<"wrong command,please input again\n";
			exit(1);
		}
	}
	//wait parent process
	else
		wait(NULL);
}
void shell::PIPE(char *argv[],int size,int all)        //size -> pos of |  all -> array length
{
	//1 -> write_end
	//0 -> read_end
	char *process1[30];char *process2[30];             //if argv = ls | more   
	for(int i = 0;i < size-1;i++)                   //process1 = ls
		process1[i] = argv[i];
	process1[size-1] = NULL;
	for(int i = 0;i<all-size;i++)                     //process2 = more
		process2[i] = argv[size+i];
	process2[all-size] = NULL;
	int fd[2];
	pid_t pid = fork();
	//child process1
	if(pid == 0)
	{
		pipe(fd);
		pid_t cpid = fork();
		//process1
		if(cpid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execvp(process1[0],process1);
		}
		//process2
		else if(cpid > 0)
		{
			dup2(fd[0],STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			execvp(process2[0],process2);
		}
	}
	//parent process
	else if(pid > 0)
		waitpid(pid,NULL,0);
}
void shell::redirection(char *argv[],int size,int all)   //the same as PIPE
{
	bool check ;                          // > or >> -> false ; < or << -> true
	char *process1[30];char *process2[30];
	for(int i=0;i<size-1;i++)
		process1[i] = argv[i];
	process1[size-1] = NULL;
	for(int i=0;i<all-size;i++)
		process2[i] = argv[size+i];
	process2[all-size] = NULL;
	if(strcmp(argv[size-1],"<") == 0 || strcmp(argv[size-1],"<<") == 0)
		check = true;
	if(strcmp(argv[size-1],">") == 0 || strcmp(argv[size-1],">>") == 0)
		check = false;
	pid_t pid = fork();
	if(pid == 0)
	{
		//if < or << 
		if(check == true)
		{
			int fd_in = open(process2[0],O_RDONLY, 0644);
			dup2(fd_in,STDIN_FILENO);
			close(fd_in);
		}
		//if > or >>
		if(check == false)
		{
			int fd_out;
			if(strcmp(argv[size-1],">>") == 0)
				fd_out = open(process2[0],O_WRONLY | O_APPEND, 0644);
			else
				fd_out = open(process2[0],O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd_out,STDOUT_FILENO);
			close(fd_out);
		}
		execvp(process1[0],process1);
	}
	else
		wait(NULL);
}
