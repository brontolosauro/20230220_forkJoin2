//
// Created by brontolosauro on 01/03/23.
//
// risoluzione espressione [(3+4)*(7-5)]+(10:2)
// devo fare in modo che
// x = 3+4
// y = 7-5
// z = 10:2
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(){

    int val, x, y, z, fd[2], status;
    pid_t p1, p2;
    //printf("p1=%d \t p2=%d \n", p1, p2);

    pipe(fd);

    p1 = fork();
    //printf("p1=%d \n", p1);
    p2 = fork();
    //printf("\t p2=%d \n",p2);
    if (p1>0 && p2>0){ //padre
        close(fd[1]); //chiudo la scrittura
        printf("sono %d; aspetto %d\n",getpid(), p2);
        waitpid(p1, &status, 0);
        read(fd[0], &z, sizeof(z));
        printf("z = 10:2 = %d \n", z);
        read(fd[0], &x, sizeof(x));
        printf("x = 3+4 = %d \n", x);
        read(fd[0], &y, sizeof(y));
        printf("y = 7-5 = %d \n", y);

        val = x*y+z;
        printf("-> risultato finale z=%d \n", val);

        /*printf("p1=%d \t p2=%d \n", p1, p2);
       printf("sono il processo padre con pid= %d\n", getpid());
       printf("mio padre ha pid= %d\n", getppid());
       printf("i miei figli hanno pid p1= %d e p2=%d\n", p1, p2);
       printf("--------------------------------------\n");*/
    }else if(p1>0 && p2==0){
        close(fd[0]); // chiudo la lettura
        val=10/2;
        printf("sono %d; aspetto %d\n",getpid(), p1);
        //waitpid(p1, &status, 0);
        printf("sono %d; invio al padre 10/2=%d\n",getpid(), val);
        write(fd[1], &val, sizeof(val));
        close(fd[1]);
       /* printf("----p1=%d \t p2=%d \n", p1, p2);
        printf("----sono il processo figlio con pid= %d\n", getpid());
        printf("----mio padre ha pid= %d\n", getppid());
        printf("----i miei fratelli dobrebbero avere hanno pid p1= %d e p2=%d\n", p1, p2);
        printf("****--------------------------------------\n");*/
        exit(0);
    } else if(p1==0 && p2>0){
        close(fd[0]); // chiudo la lettura
        val=7-5;
        printf("sono %d; aspetto %d\n",getpid(), p2);
        waitpid(p2, &status, 0);
        printf("sono %d; invio al padre 7-5=%d\n", getpid(), val);
        write(fd[1], &val, sizeof(val));
        close(fd[1]);
        /*printf("--p1=%d \t p2=%d \n", p1, p2);
        printf("--sono il processo figlio con pid= %d\n", getpid());
        printf("--mio padre ha pid= %d\n", getppid());
        printf("--i miei fratelli dobrebbero avere hanno pid p1= %d e p2=%d\n", p1, p2);
        printf("**--------------------------------------\n");*/
        exit(0);
    }else if(p1==0 && p2==0){
        close(fd[0]); // chiudo la lettura
        val=3+4;
        printf("sono %d; invio al padre 3+4=%d\n", getpid(), val);
        write(fd[1], &val, sizeof(val));
        close(fd[1]);

        /*printf("------p1=%d \t p2=%d \n", p1, p2);
        printf("------sono il processo figlio con pid= %d\n", getpid());
        printf("------mio padre ha pid= %d\n", getppid());
        printf("------i miei fratelli dobrebbero avere hanno pid p1= %d e p2=%d\n", p1, p2);
        printf("******--------------------------------------\n");*/
        exit(0);
    }//else {
       /* printf("sono di nuovo il processo padre con pid= %d\n", getpid());
        printf("i miei figli hanno pid p1= %d e p2=%d\n", p1, p2);
        printf("--------------------------------------\n");*/
    //}

    return 0;



}


