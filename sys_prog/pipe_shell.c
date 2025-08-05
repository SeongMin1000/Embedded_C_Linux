#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 100

// 명령어 문자열을 공백으로 나눠서 argv 배열로 변환
void parse_command(char *cmd, char **args)
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

int main()
{
    char line[MAX_LINE];

    while (1)
    {
        printf("mini-shell$ ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            break;
        }

        // 줄바꿈 제거
        line[strcspn(line, "\n")] = '\0';

        // 종료
        if (strcmp(line, "exit") == 0)
            break;

        // '|' 기준으로 두 명령어로 나누기
        char *cmd1 = strtok(line, "|");
        char *cmd2 = strtok(NULL, "|");

        if (cmd2 == NULL)
        {
            // 파이프 없는 단일 명령어
            char *args[MAX_ARGS];
            parse_command(cmd1, args);

            pid_t pid = fork();
            if (pid == 0)
            {
                execvp(args[0], args);
                perror("execvp 실패");
                exit(1);
            }
            else
            {
                waitpid(pid, NULL, 0);
            }
        }
        else
        {
            // 파이프 있는 두 명령어 처리
            int pipefd[2];
            if (pipe(pipefd) == -1)
            {
                perror("pipe 실패");
                continue;
            }

            pid_t pid1 = fork();
            if (pid1 == 0)
            {
                // 첫 번째 명령: stdout을 파이프에 연결
                close(pipefd[0]);               // 읽기 닫기
                dup2(pipefd[1], STDOUT_FILENO); // 출력 -> 파이프 쓰기
                close(pipefd[1]);

                char *args1[MAX_ARGS];
                parse_command(cmd1, args1);
                execvp(args1[0], args1);
                perror("execvp 실패");
                exit(1);
            }

            pid_t pid2 = fork();
            if (pid2 == 0)
            {
                // 두 번째 명령: stdin을 파이프에서 읽기
                close(pipefd[1]);              // 쓰기 닫기
                dup2(pipefd[0], STDIN_FILENO); // 입력 <- 파이프 읽기
                close(pipefd[0]);

                char *args2[MAX_ARGS];
                parse_command(cmd2, args2);
                execvp(args2[0], args2);
                perror("execvp 실패");
                exit(1);
            }

            // 부모는 pipe 닫고 자식들 대기
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }

    return 0;
}
