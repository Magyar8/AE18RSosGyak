#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>


void do_nothing();


int main ()
{


	signal(SIGALRM, do_nothing);
	printf("varok de meddig?\n");
	pause();
    	printf("  Vegre, itt az alarm \n");
}	
void do_nothing(){ ;}
