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
    
    /*buf[0] = 0;*/
    
    rsz=0;

    
    ret = mkfifo("ae18rs", 0777);	                        // letrehozom a fifo-t a filerendszeren
	if (ret == -1) {
	    perror("mkfifo() hiba!");
	    exit(-1);
	}
    
    
    fd=open("ae18rs", O_RDWR);
    if (fd==-1){
        perror("mkfifo() hiba!");
	    exit(-1);    
    }

    ret = read(fd, &rsz, sizeof(int));                      // olvasok belole ugyanazt, ret: mennyit sikerult olvasni
	printf("kapott szam: %d, (%dbyte) \n", rsz, ret);  

    rszd=2*rsz;

    printf("vissza a duplaja: %d (%ldbyte)\n", rszd, sizeof(int));
	write(fd, &rszd, sizeof(int));
    
    close(fd);
    
    return 0;
}
