#include <stdio.h>
#include <stdint.h>

// --- ��Ʈ ����ũ ���� �Լ��� ---

// 1. n��° ��Ʈ �ѱ�
uint32_t set_bit(uint32_t value, int n)
{
    return value | (1U << n);
}

// 2. n��° ��Ʈ ����
uint32_t clear_bit(uint32_t value, int n)
{
    return value & ~(1U << n);
}

// 3. n��° ��Ʈ ������
uint32_t toggle_bit(uint32_t value, int n)
{
    return value ^ (1U << n);
}

// 4. ���� ���� 1��Ʈ�� �����
uint32_t lowest_bit(uint32_t value, int n)
{
    return value & -value; // n�� ��� �� ��
}

// 5. ���� ���� 1��Ʈ �����
uint32_t remove_lowest_bit(uint32_t value, int n)
{
    return value & (value - 1); // n�� ��� �� ��
}

// ���̳ʸ� �� ���
void print_binary(uint32_t value)
{
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (value >> i) & 1); // i��° ��Ʈ�� ����
        if (i % 8 == 0 && i != 0)
            printf(" "); // ���� ���� 8��Ʈ ������ ���
    }
}

// --- �Լ� ������ ���̺� Ÿ�� ---
typedef uint32_t (*bit_func)(uint32_t, int);

// --- �Լ� �̸� �迭 (������) ---
const char *func_names[] = {
    "Set Bit", "Clear Bit", "Toggle Bit",
    "Get Lowest 1-bit", "Remove Lowest 1-bit"};

// --- main ---
int main()
{
    // �Լ� ���̺�
    bit_func funcs[] = {
        set_bit,
        clear_bit,
        toggle_bit,
        lowest_bit,
        remove_lowest_bit};

    // �׽�Ʈ�� ��
    uint32_t value = 0b01011000;
    int n = 3;

    // ��� �Լ� �׽�Ʈ
    for (int i = 0; i < 5; i++)
    {
        uint32_t result = funcs[i](value, n);
        printf("���̳ʸ� ��: ");
        print_binary(result);
        printf("[%d] %s: 0x%08X (%u)\n", i, func_names[i], result, result);
    }

    return 0;
}
