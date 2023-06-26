#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int fd[2], i;
	
	pipe(fd);

	for (i = 0; i < 2; i++) {
		if((pid = fork()) == 0) {
			break;
        }
    }

	if (i == 0) {			//兄
		close(fd[0]);				//写,关闭读端
		dup2(fd[1], STDOUT_FILENO);		
		execlp("ls", "ls", NULL);	
	} else if (i == 1) {	//弟
		close(fd[1]);				//读，关闭写端
		dup2(fd[0], STDIN_FILENO);		
		execlp("wc", "wc", "-l", NULL);		
	} else {
        close(fd[0]);
        close(fd[1]);
		for(i = 0; i < 2; i++)		//两个儿子wait两次
			wait(NULL);
	}

	return 0;
}
