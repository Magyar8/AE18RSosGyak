#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char * argv[],char * env[]){

	int status, pid, ppid, gpid;
	
	ppid = getpid();        /* Szulo pid-jet elkaptuk */

	/* innentol a gyermek processz */

	if ((pid = fork()) == 0){ 	
		printf("\n A gyermek pid = %d \n", getpid());
		status = execl("./child" ,"ls", "-l", (char *)NULL); 
		if (status == -1){
			perror("parent execl failed");
			exit (0);
		}
	}

	/* innentol ujra a szulo process */
	
	printf("\n %d.sz. szulo var a %d.sz. gyermekre.\n ", ppid,pid);
	if (pid != wait(&status)) perror(" Szulo - varakozas hiba ");
	return 0;
}
