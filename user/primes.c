#include "kernel/stat"
#include "kernel/types"
#include "user/user.h"

int main(void) {
    int a1 = 2;
    int a2 = 3;
    int state = fork();
    if (state < 0) {
        printf("创建子进程失败");
    }
    else if (state == 0) {

    }
}
void process(int p[2]) {
    close(0);
    dup(p[0]);
    close(p[0]);
    close(p[1]);
    int* buf, prime;
    int fd[2];
    if (read(0, prime, 4)) {
        printf("prime number: %d\n", &prime); // 打印由父进程传来的第一个数字
        pipe(fd);
        if (fork() > 0) {
            while (read(0, buf, 4)) {
                if ((&buf) % (&prime) != 0)
                    write(fd[1], buf, 4);
            }
            close(fd[1]);
            close(0);
        }
        else {
            process(fd);
        }
    }
}
