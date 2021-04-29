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
    int fd, ret;
    char buf[32];
    
    buf[0] = 0;
    
    ret = mkfifo("ae18rs", 0777);	            // letrehozom a fifo-t a filerendszeren
	if (ret == -1) {
	    perror("mkfifo() hiba!");
	    exit(-1);
	}
    
    
    fd=open("ae18rs", O_RDWR);
    if (fd==-1){
        perror("mkfifo() hiba!");
	    exit(-1);    
    }

    ret = read(fd, buf, 32);                    // olvasok belole ugyanazt, ret: mennyit sikerult olvasni
	printf("olvasok a fifobol\n%s (%d byte)\n", buf, ret);
    close(fd);
	unlink("ae18rs");	                        // letorlom a fifomat az fs-rol
    
    return 0;
}
