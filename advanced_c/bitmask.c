#include <stdio.h>
#include <stdint.h>

// --- 비트 마스크 관련 함수들 ---

// 1. n번째 비트 켜기 (set)
uint32_t set_bit(uint32_t value, int n)
{
    return value | (1U << n);
}

// 2. n번째 비트 끄기 (clear)
uint32_t clear_bit(uint32_t value, int n)
{
    return value & ~(1U << n);
}

// 3. n번째 비트 토글 (반전)
uint32_t toggle_bit(uint32_t value, int n)
{
    return value ^ (1U << n);
}

// 4. 가장 낮은 위치의 1비트만 남기기
uint32_t lowest_bit(uint32_t value, int n)
{
    return value & -value;
}

// 5. 가장 낮은 위치의 1비트 제거
uint32_t remove_lowest_bit(uint32_t value, int n)
{
    return value & (value - 1);
}

// 이진수 출력
void print_binary(uint32_t value)
{
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (value >> i) & 1);
        if (i % 8 == 0 && i != 0)
            printf(" ");
    }
}

// --- 함수 포인터 타입 ---
typedef uint32_t (*bit_func)(uint32_t, int);

// --- 함수 이름 배열 (설명용) ---
const char *func_names[] = {
    "Set Bit", "Clear Bit", "Toggle Bit",
    "Get Lowest 1-bit", "Remove Lowest 1-bit"};

// --- main ---
int main()
{
    // 함수 배열
    bit_func funcs[] = {
        set_bit,
        clear_bit,
        toggle_bit,
        lowest_bit,
        remove_lowest_bit};

    // 테스트용 값
    uint32_t value = 0b01011000;
    int n = 3;

    // 함수 테스트
    for (int i = 0; i < 5; i++)
    {
        uint32_t result = funcs[i](value, n);
        printf("이진수 출력: ");
        print_binary(result);
        printf(" [%d] %s: 0x%08X (%u)\n", i, func_names[i], result, result);
    }

    return 0;
}
