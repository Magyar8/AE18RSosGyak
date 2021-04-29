#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fd, ret;
	char buf[32];

	buf[0] = 0;


        ret = mkfifo("ae18rs", 00666);	        // letrehozom a fifo-t a filerendszeren
	if (ret == -1) {
	    perror("mkfifo() hiba!");
	    exit(-1);
	}

	fd = open("ae18rs", O_RDWR);	            // megnyitom a fifot amit az iment hoztam letre
	if (fd == -1) {
	    perror("open() hiba!");
	    exit(-1);
	}

	strcpy(buf, "A hallgato neve: Magyar Balazs");
	printf("irok a fifoba\n%s(%ld byte)\n", buf, strlen(buf));
	write(fd, buf, strlen(buf));                // irok bele valamit, hogy ne legyen ures

	ret = read(fd, buf, 32);                    // olvasok belole ugyanazt, ret: mennyit sikerult olvasni
	printf("olvasok a fifobol\n%s (%d byte)\n", buf, ret);

	close(fd);

	unlink("ae18rs");	                        // letorlom a fifomat az fs-rol
}

/*
irok a fifoba: ezt teszem a fifoba:19
read() olvasott 19 byteot, ami a kovetkezo: ezt teszem a fifoba
*/

