# 컴파일러 지정
CC = gcc

# -MMD: .d 파일 생성
# -MP: 삭제된 헤더로 인한 오류 방지용 dummy 타겟 추가
CFLAGS = -Wall -g -MMD -MP

# 타겟 이름
TARGET = main

# 소스 및 오브젝트 파일 목록
SRCS = main.c add.c
OBJS = $(SRCS:.c=.o)

# 기본 빌드 규칙
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


# 개별 .c -> .o 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# 정리 규칙
clean:
	rm -f $(OBJS) $(TARGET) $(OBJS:.o=.d)

# 자동 의존성 포함
-include $(OBJS:.o=.d)
