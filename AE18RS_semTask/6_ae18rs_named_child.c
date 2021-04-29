#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/wait.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(){
    int ret, rsz, rszd;
    int fd;
    /*char buf[16];*/

    srand(time(NULL));
    /*buf[0] = 0;*/
    rsz = 0;
    rsz = rand()%100;

    
    fd=open("ae18rs", O_RDWR);
    if (fd==-1){
        perror("mkfifo() hiba!");
	    exit(-1);    
    }

    /*strcpy(rsz);*/
	printf("irok a fifoba: %d (%ldbyte)\n", rsz, sizeof(int));
	write(fd, &rsz, sizeof(int));

    wait(NULL);

    ret = read(fd, &rszd, sizeof(int));                     // olvasok belole ugyanazt, ret: mennyit sikerult olvasni
	printf("visszakapott szam: %d, (%dbyte) \n", rszd, ret);

    close(fd);

    unlink("ae18rs");	                                    // letorlom a fifomat az fs-rol
    
    return 0;
}
