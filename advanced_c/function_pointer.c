#include <stdio.h>

// 두 수를 더하는 함수
int add(int a, int b)
{
    return a + b;
}

// 두 수를 빼는 함수
int sub(int a, int b)
{
    return a - b;
}

int main(void)
{
    int a, b;
    scanf("%d %d", &a, &b);

    // [선언] 함수 포인터 선언: (매개변수 타입)(매개변수 이름) 형식
    // 함수의 주소를 저장하기 위한 함수 포인터
    int (*p_cal)(int, int);

    // [할당] 함수 포인터 = 함수 주소
    p_cal = &add;
    // [호출] (*함수포인터)(인자들) 또는 함수포인터(인자들) 형식으로 호출 가능
    int result = p_cal(a, b);
    printf("덧셈 결과: %d\n", result);

    // [재할당] 함수 포인터 = 다른 함수 주소
    p_cal = &sub;
    // [호출] 마찬가지로 호출
    result = p_cal(a, b);
    printf("뺄셈 결과: %d\n", result);

    return 0;
}
