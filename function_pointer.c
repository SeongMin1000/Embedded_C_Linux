#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int main(void)
{
    int a, b;
    scanf("%d %d", &a, &b);

    // [����] ��ȯ�� (*������_�̸�)(�Ű�����_Ÿ��_���);
    // �ݵ�� ��ȣ �ȿ� ������ �̸��� �־����
    int (*p_cal)(int, int);

    // [�Ҵ�] ������_�̸� = &�Լ���;
    p_cal = &add;
    // [ȣ��] (*������_�̸�)(�Ű�����_��)  �Ǵ� ������_�̸�(�Ű�����_��);
    int result = p_cal(a, b);
    printf("���� ���: %d\n", result);

    // [���Ҵ�] ������_�̸� = &�Լ���;
    p_cal = &sub;
    // [ȣ��] (*������_�̸�)(�Ű�����_��)  �Ǵ� ������_�̸�(�Ű�����_��);
    result = p_cal(a, b);
    printf("���� ���: %d\n", result);
    return 0;
}