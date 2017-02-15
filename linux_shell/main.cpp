#include<iostream>
#include<string>
#include<cstring>
#include<sstream>
#include<readline/readline.h>
#include<readline/history.h>
#include"shell.h"
using namespace std;
int main()
{
	shell sh;
	char *cmd[50];
	char *input;
	while((input = readline(sh.hostname().c_str())) != NULL)
	{
		//r_check -> redirection;check -> pipe;eod -> end of file
		bool r_check = false,check = false,eof = true;
		int size = 0;
		int count = 0;       //size of 2's array
		eof = false;
		//char * -> string
		string argv;
		stringstream ss;  
		ss<<input;
		while(getline(ss,argv,' '))
		{
			if(argv == "exit" && count == 0)
			{
				cout<<"Byebye!\n";
				return 0;
			}
			//string to char
			char *str = new char[argv.length() + 1];
			strcpy(str, argv.c_str());
			cmd[count] = str;     //store into second array
			count++;
			//if pipe
			if(argv == "|")
			{
				check = true;
				size = count;
			}
			//if redirection
			if(argv == "<" || argv == "<<" || argv == ">" || argv == ">>")
			{
				r_check = true;
				size = count;
			}
		}
		add_history(input);
		cmd[count] = NULL;
		if(eof)
		{
			cout<<"\nByebye!";
			return 0;
		}
		if(r_check == true)
			sh.redirection(cmd,size,count);
		if(check == true)
			sh.PIPE(cmd,size,count);
		if(check == false && r_check == false)
			sh.exec(cmd);
		free(input);
		for(int i=0;i<count;i++)
			cmd[i]=NULL;
	}
	return 0;
}
