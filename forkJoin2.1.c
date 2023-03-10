//
// Created by brontolosauro on 02/03/23.
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

void elaborazioneParallela(int fd[]);

int main(){

    int val, status, x, y, z, fd[2], pid;
    pid_t p1;
    pipe(fd);

    p1=fork();

    if (p1==0){
        elaborazioneParallela(fd);
        exit(0);
    } else {
        z = 10/2;
        close(fd[1]);
        pid = wait(&status);
        if(WIFEXITED(status)){
            printf("Terminazione volontaria di %d con stato %d \n", pid, WEXITSTATUS(status));
            read(fd[0], &x, sizeof(x));
            printf("sono %d e ho ricevuto x = 3+4 = %d\n", getpid(), x);
            read(fd[0], &y, sizeof(y));
            printf("sono %d e ho ricevuto x = 7-5 = %d\n", getpid(), y);
            val = x*y+z;
            printf("-> [(3+4)*(7-5)]+(10:2)=%d ", val);
        }else{
            if (WIFSIGNALED(status)){
                printf("terminazione involontaria di %d per segnale %d \n ", pid, WTERMSIG(status));
            }
        }

    }


}

void elaborazioneParallela(int fd[]){ //secondo me gli devo passare il file descriptor
    pid_t p2;
    int val, x, y, status, pid;

    p2 = fork();
    if (p2==0){
        close(fd[0]);
        x = 3+4;
        printf("sono %d e sto inviando il risultato di x = 3+4 = %d\n", getpid(), x);
        write(fd[1], &x, sizeof(x));
        exit(0);
    }
    else{
        close(fd[0]);
        y=7-5;
        pid = wait(&status);
        if(WIFEXITED(status)){
            printf("Terminazione volontaria di %d con stato %d \n", pid, WEXITSTATUS(status));
            printf("sono %d e sto inviando il risultato di y = 7-5 = %d\n", getpid(), y);
            write(fd[1], &y, sizeof(y));
            exit(0);
        }else{
            if (WIFSIGNALED(status)){
                printf("terminazione involontaria di %d per segnale %d \n ", pid, WTERMSIG(status));
                exit(1);
            }
        }
    }
}