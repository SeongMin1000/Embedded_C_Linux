# 컴파일러 지정
CC = gcc
CFLAGS = -Wall -g

# 타겟 이름
TARGET = main

# 소스 및 오브젝트 파일 목록
OBJS = main.o add.o

# 기본 빌드 규칙
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 개별 .c -> .o 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# 정리 규칙
clean:
	rm -f *.o $(TARGET)
