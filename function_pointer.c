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

    // [선언] 반환형 (*포인터_이름)(매개변수_타입_목록);
    // 반드시 괄호 안에 포인터 이름을 넣어야함
    int (*p_cal)(int, int);

    // [할당] 포인터_이름 = &함수명;
    p_cal = &add;
    // [호출] (*포인터_이름)(매개변수_값)  또는 포인터_이름(매개변수_값);
    int result = p_cal(a, b);
    printf("덧셈 결과: %d\n", result);

    // [재할당] 포인터_이름 = &함수명;
    p_cal = &sub;
    // [호출] (*포인터_이름)(매개변수_값)  또는 포인터_이름(매개변수_값);
    result = p_cal(a, b);
    printf("뺄셈 결과: %d\n", result);
    return 0;
}