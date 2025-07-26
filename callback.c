#include <stdio.h>

// --- LED 제어 함수들 (단순 동작 함수들) ---

void turn_led_on(void)
{
    printf("LED ON\n");
}

void turn_led_off(void)
{
    printf("LED OFF\n");
}

void toggle_led(void)
{
    // led_state는 함수 내부에서 유지돼야 하므로 static으로 선언
    static int led_state = 0; // 0: OFF, 1: ON

    if (led_state == 0)
    {
        printf("LED ON (Toggled)\n");
        led_state = 1;
    }
    else
    {
        printf("LED OFF (Toggled)\n");
        led_state = 0;
    }
}

// --- 버튼 콜백 시스템 (함수 포인터 활용) ---

// 등록된 콜백 함수 포인터 전역 변수. '전역 함수 포인터' 역할
void (*g_button_callback)(void) = NULL;

// 콜백 함수(함수 포인터)를 시스템에 등록하는 함수
// '함수 포인터'를 인자로 받음
void register_button_callback(void (*callback_to_register)(void))
{
    g_button_callback = callback_to_register;
    printf(">> 새로운 버튼 콜백이 등록되었습니다.\n");
}

// 버튼이 눌렸을 때의 이벤트 시뮬레이션
void simulate_button_press(void)
{
    printf("버튼 눌림! ");
    // 등록된 콜백 함수가 있는지 확인하고, 있다면 호출
    if (g_button_callback != NULL)
    {
        g_button_callback(); // 콜백 호출!
    }
    else
    {
        printf("아직 콜백이 등록되지 않음.\n");
    }
}

// --- 메인 함수 (테스트 코드) ---

int main(void)
{
    // 버튼을 'LED 켜기' 동작으로 등록 후 테스트
    register_button_callback(&turn_led_on);
    simulate_button_press();

    printf("\n");

    // 버튼을 'LED 토글' 동작으로 변경 후 여러 번 테스트
    register_button_callback(&toggle_led);
    simulate_button_press();
    simulate_button_press();
    simulate_button_press();

    return 0;
}
