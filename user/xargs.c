#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
//#define MAX_ARGS 10
#define BUFFER_SIZE 512

void parse_args(char *buffer, char **args, int max_args) {
    char *p = buffer;
    int arg_index = 0;

    while (*p) {
        // 跳过空格和换行符
        while (*p == ' ' || *p == '\n') p++;
        if (*p == '\0') break;  // 检查是否是字符串结尾

        // 开始一个新参数
        if (arg_index < max_args - 1) {
            args[arg_index++] = p;
        } else {
            fprintf(2, "parse_args: too many arguments\n");
            exit(1);
        }

        // 移动到当前参数的结尾
        while (*p != ' ' && *p != '\n' && *p != '\0') p++;
        if (*p == '\0') break;  // 检查是否是字符串结尾

        // 结尾处换成字符串结束符
        *p++ = '\0';
    }

    // 参数数组以NULL结尾
    args[arg_index] = 0;
}

int main(int argc, char *argv[]) {
    char arg_buffer[BUFFER_SIZE];
    char *args[MAXARG];
    int n;

    // 初始化参数数组
    for (int i = 1; i < argc && i < MAXARG - 1; i++) {
        args[i - 1] = argv[i];
    }
    
    // 从标准输入读取数据
    while ((n = read(0, arg_buffer, sizeof(arg_buffer) - 1)) > 0) {
        arg_buffer[n] = '\0'; // 确保字符串以NULL结束

        // 解析参数
        parse_args(arg_buffer, args + argc - 1, MAXARG - argc + 1);

        // 使用解析后的参数执行命令
        if (fork() == 0) {
            exec(args[0], args);
            fprintf(2, "exec %s failed\n", args[0]);
            exit(1);
        } else {
            wait(0);
        }
    }

    if (n < 0) {
        fprintf(2, "read error\n");
        exit(1);
    }

    exit(0);
}