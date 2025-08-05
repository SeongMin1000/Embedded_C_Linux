#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 100

int main(int argc, char *argv[])
{
    char line[MAX_LINE];

    while (1)
    {
        printf("mini-shell$ ");
        fflush(stdout);

        // 입력 받기
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            break;
        }

        // 줄바꿈 문자 제거
        line[strcspn(line, "\n")] = '\0';

        // 종료 명령어
        if (strcmp(line, "exit") == 0)
            break;

        // 명령어 분리
        char *args[MAX_ARGS];
        int i = 0;
        char *token = strtok(line, " ");
        while (token != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // execvp에 넘길 때 NULL 종료 필요

        if (i == 0)
            continue; // 공백만 입력된 경우

        // fork + exec + wait
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork 실패");
            continue;
        }

        if (pid == 0)
        {
            // 자식: 명령어 실행
            execvp(args[0], args);
            perror("exec 실패");
            exit(EXIT_FAILURE);
        }
        else
        {
            // 부모: 자식 종료 대기
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
