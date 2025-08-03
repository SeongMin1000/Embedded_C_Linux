# 디렉토리 설정
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# 컴파일러 및 플래그
CC = gcc
CFLAGS = -Wall -g -MMD -MP -I$(INC_DIR)

# 소스 및 오브젝트 파일
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# 최종 실행 파일
TARGET = main

# 빌드
all: $(TARGET)

# 타겟 빌드(링크)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 컴파일 (소스 -> 오브젝트)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 전체 재빌드
rebuild: clean all

# 클린
clean:
	rm -f $(OBJS) $(TARGET) $(OBJS:.o=.d)

# 의존성 포함
-include $(DEPS)

# 항상 실행해야 하는 가짜 타겟들 선언
.PHONY: all rebuild clean
