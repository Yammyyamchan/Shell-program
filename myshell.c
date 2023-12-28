#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#define MAX_PATH 3
#define MAX_SIZE 256

int sig = 0;

void handler(int signo)
{
	if(signo==SIGINT)	
		sig=1;
	if(signo==SIGQUIT)
		sig=1;
	if(signo==SIGTSTP)
		sig=1;
}

int main() {

    int fd;
    char *path[MAX_PATH];
    char *home="/home/psc";
    char buf[MAX_SIZE],line[MAX_SIZE];

    char *u_id = "Park.Myshell@";
    if ((fd = open("PATH", O_RDONLY)) == -1) {
        perror("PATH");
        exit(-1);
    }
   
    read(fd, buf, MAX_SIZE);

    char* str=strtok(buf, ":\n ");
    path[0] = str;

    str = strtok(NULL, ":\n ");
    path[1] = str;

    str = strtok(NULL, ":\n ");
    path[2] = str;

    close(fd);

    if(chdir(home)==-1)
    {
    	perror("chdir");
	exit(0);
    }

    signal(SIGINT,handler);
    signal(SIGQUIT,handler);
    signal(SIGTSTP,handler);

    while (1) {
    
        int count = 0;
	int pi_index = 0;
	char *arg[32];
	char *pt=NULL;
	str=NULL;

	printf("\x1b[32m%s",u_id);
	printf("\x1b[0m:");
        printf("\x1b[34m%s",getcwd(pt,MAX_SIZE));
	printf("\x1b[0m$ ");
	printf("\x1b[0m");
	
	memset(line,0,sizeof(line));
        fgets(line, MAX_SIZE, stdin);
	       
        str = strtok(line, "\n ");
        arg[0] = str;

        for(int i = 1; str != NULL; i++)
	{
            str = strtok(NULL, "\n ");
	    arg[i]=str;
        }

	if(sig == 1){
		sig = 0;
		continue;
	}

        if (strcmp(arg[0], "exit") == 0) {
            printf("Exit myshell Program.\n");
            exit(1);
        }
        

	if(strcmp(arg[0],"cd") == 0)
	{	
		if((arg[1] == NULL) ||(strcmp(arg[1],"~")==0))
		{
			if(chdir(home)==0)
				continue;
		}
		
		if(chdir(arg[1]) == 0)
			continue;
			
		else{
			printf("Error Directory\n");
			continue;
		}

	}
	
	for(int i=0;arg[i]!=NULL;i++)
	{
		if(strcmp(arg[i],"|")==0)
		{
			pi_index=i;
			arg[i]=NULL;
			break;
		}
	}

        if(pi_index!=0)
	{
		int pi[2];
		if(pipe(pi) == -1)
		{
			perror("Error Pipe\n");
			continue;
		}
						
		if(fork() == 0)
		{
			close(1);
			dup(pi[1]);
			close(pi[0]);
			close(pi[1]);
			execvp(arg[0],arg);
			printf("pipe exec error\n");
			exit(3);
		}
			
				
		if(fork() == 0)
		{
			close(0);
			dup(pi[0]);
			close(pi[0]);
			close(pi[1]);
			execvp(arg[pi_index+1],arg+(pi_index+1));
			printf("pipe exec error\n");
			exit(4);
		}
		close(pi[0]);
		close(pi[1]);
		while(wait((int *)0) != -1)
			;
		continue;
	}
		
	
       	 for (int i = 0; i < MAX_PATH; i++)
	 {
       	    char aPath[50];
	    sprintf(aPath, "%s/%s", path[i], arg[0]);

		if (access(aPath, F_OK) == 0)
		{
		 	if (fork() == 0)
			{
                  	 	 execv(aPath, arg);
              		 	 printf("Failed command.\n");
              		 	 exit(2);
			}

      			wait((int *)0);
			break;

          	  }

	  	  else
		  {
		       	count++;
			continue;
          	  }
          	 
      	  }

       	 if (count == MAX_PATH)
       		    printf("Command not found\n");
	}
}

