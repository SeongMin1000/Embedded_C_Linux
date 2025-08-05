// ex) free -h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "사용법: %s <명령어> [인자...]\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork 실패");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // 자식 프로세스: argv[1]부터 명령어 및 인자로 execvp 호출
        execvp(argv[1], &argv[1]);

        // execvp 실패 시
        perror("execvp 실패");
        exit(EXIT_FAILURE);
    }
    else
    {
        // 부모 프로세스: 자식 프로세스 종료 대기
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("자식 프로세스 정상 종료, 종료 코드: %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("자식 프로세스 비정상 종료\n");
        }
    }

    return 0;
}
