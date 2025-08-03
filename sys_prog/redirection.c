// ex) ls > output.txt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "사용법: %s <출력_파일명>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1]; // 파일 이름
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("파일 열기 실패");
        exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2 실패");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("이 내용은 터미널이 아니라 %s에 저장됩니다.\n", filename);

    close(fd);
    return 0;
}
