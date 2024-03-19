#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"
void process(int p[2]);
int main(void) {
    //int state = fork();
    int p[2];
    pipe(p);
    if (fork() == 0) {
        process(p);
    }
    else{
        close(p[0]);
        for (int j=2;j<50;j++){
            write(p[1],&j,sizeof(j));
        }
        close(p[1]);
    }
    //wait(0);
    exit(0);
}

void process(int p[2]) {
    //close(p[1]);
    int buf=0;
    int prime=0;
    int fd[2];
    if (read(p[0], &prime, sizeof(prime))) {
        //printf("%d:prime number: %d\n", getpid(), prime); // 打印由父进程传来的第一个数字
        printf("prime %d\n", prime);
        pipe(fd);
        if (fork() > 0) {
            close(fd[0]);
            while (read(p[0], &buf, 4)) {
                if ((buf) % (prime) != 0)
                    write(fd[1], &buf, 4);
            }
            close(p[1]);
            close(p[0]);
            close(fd[1]);
        }
        else {
            process(fd);
        }
        //wait(0);
        //exit(0);
    }
}
