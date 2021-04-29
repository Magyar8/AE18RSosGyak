#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];              // 2 elemu tomb, mert ket vege lesz a csonek, ezert ket valtozo neki
    pid_t cpid;                 // gyerek pidje lesz benne
    char buf;                   // buffer
    char szoveg[32];            // masik buffer a kuldendo szovegnek
    int ret;

    if (pipe(pipefd) == -1) {	// krealunk csovezeteket, es a ket fd a pipefd-ben lesz tarolva
	    perror("pipe");
	    exit(-1);
    }

    /* printf("%d: fd1: %d, fd2: %d\n", getpid(), pipefd[0], pipefd[1]); */

    cpid = fork();
    if (cpid == -1) {
	    perror("fork");
	    exit(-1);
    }

    if (cpid == 0) {            /* gyerek vagyok */
        /*printf("%d: gyerek vagyok\n", getpid());*/     //ez a cső most nem kell
                                /*gyerek vagyok nem olvasok csak irok csukjuk be ezt egybol*/
	    close(pipefd[0]);	    /* na itt becsukom mar az olvaso veget is */


        printf("%d: gyerek vagyok\n", getpid());
        strcpy(szoveg, "MB ae18rs");                    // feltoltom a buffert a kuldeni kivant stringgel
        printf("%d: kuldom a szoveget: %s (%ld db. karakter)\n", getpid(), szoveg, strlen(szoveg));

        write(pipefd[1], szoveg, strlen(szoveg));	    // ontunk anyagot a csobe

        close(pipefd[1]);       /* a gyerek befejezte az irast, ezert az iras fd-t le is csukom */ 
        exit(0);	                                    // kilep
    }

    else {	                    /* szulo vagyok */
        printf("%d: szulo vagyok\n", getpid());
        close(pipefd[1]);       /* lecsukom a csatorna fedelet, a masik oldalon EOF lesz */


        wait(NULL);             /* varjunk gyerekre */
        printf("%d: megnezem mi van a csoben\n%d: ", getpid(), getpid());
   	    while (read(pipefd[0], &buf, 1) > 0) {	        // olvasunk a cso kimeneterol, amig van mit (1 byteonkent)
		    printf("%c", buf);
	    }
        printf("\n");
        close(pipefd[0]);       /* itt meg az olvaso veget csukjuk le */

	    wait(NULL);             /* varjunk gyerekre */
        exit(0);
    }
}

/* Az eredmeny ehhez hasonlo lehet:

25261: fd1: 3, fd2: 4
25261: szulo vagyok
25261: kuldom a szoveget: ez itt kerem egy szoveg (23 db. karakter)
25262: gyerek vagyok
25262: megnezem mi van a csoben
25262: ez itt kerem egy szoveg
25262: lezartak a cso masik oldalat

*/
