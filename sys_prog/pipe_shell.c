#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_CMDS 10
#define MAX_ARGS 100

// 문자열을 공백 기준으로 나누어 args 배열에 저장
void parse_args(char *cmd, char **args)
{
    int i = 0;
    char *token = strtok(cmd, " ");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

int main(int argc, char *argv[])
{
    char line[MAX_LINE];

    while (1)
    {
        printf("mini-shell$ ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        // 개행 제거
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0)
            break;

        // 1. 파이프 단위로 분리
        char *cmds[MAX_CMDS];
        int cmd_count = 0;

        char *token = strtok(line, "|");
        while (token != NULL && cmd_count < MAX_CMDS)
        {
            cmds[cmd_count++] = token;
            token = strtok(NULL, "|");
        }

        // 2. 파이프 생성
        int pipefds[2 * (cmd_count - 1)];
        for (int i = 0; i < cmd_count - 1; i++)
        {
            if (pipe(pipefds + i * 2) < 0)
            {
                perror("pipe 실패");
                exit(EXIT_FAILURE);
            }
        }

        // 3. fork + exec + dup2 체인
        for (int i = 0; i < cmd_count; i++)
        {
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("fork 실패");
                exit(EXIT_FAILURE);
            }

            if (pid == 0)
            {
                // stdin 설정
                if (i != 0)
                {
                    dup2(pipefds[(i - 1) * 2], 0);
                }

                // stdout 설정
                if (i != cmd_count - 1)
                {
                    dup2(pipefds[i * 2 + 1], 1);
                }

                // 사용하지 않는 파이프 닫기
                for (int j = 0; j < 2 * (cmd_count - 1); j++)
                {
                    close(pipefds[j]);
                }

                // 명령어 파싱 및 실행
                char *args[MAX_ARGS];
                parse_args(cmds[i], args);
                execvp(args[0], args);
                perror("exec 실패");
                exit(EXIT_FAILURE);
            }
        }

        // 부모 프로세스는 파이프 닫고 자식 대기
        for (int i = 0; i < 2 * (cmd_count - 1); i++)
        {
            close(pipefds[i]);
        }

        for (int i = 0; i < cmd_count; i++)
        {
            wait(NULL);
        }
    }

    return 0;
}
