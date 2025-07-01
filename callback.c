#include <stdio.h>

// --- LED 제어 함수들 (실제 콜백이 될 함수들) ---

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
    // led_state는 함수가 끝나도 값을 기억해야 하므로 static으로 선언
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

// --- 버튼 드라이버 (콜백 시스템) ---

// 등록될 콜백 함수를 저장할 함수 포인터. '연결고리' 역할.
void (*g_button_callback)(void) = NULL;

// 실행할 함수(콜백)를 시스템에 등록하는 함수
// '함수 포인터'를 인자로 받음
void register_button_callback(void (*callback_to_register)(void))
{
    g_button_callback = callback_to_register;
    printf(">> 새로운 기능이 버튼에 등록되었습니다.\n");
}

// 버튼이 눌리는 이벤트를 시뮬레이션
void simulate_button_press(void)
{
    printf("버튼 눌림! ");
    // 등록된 콜백 함수가 있는지 확인하고, 있다면 호출한다.
    if (g_button_callback != NULL)
    {
        g_button_callback(); // 콜백 호출!
    }
    else
    {
        printf("아무 기능도 등록되지 않음.\n");
    }
}

// --- 메인 함수 (시나리오) ---

int main(void)
{
    // 버튼에 'LED 켜기' 기능 등록 후 누르기
    register_button_callback(&turn_led_on);
    simulate_button_press();

    printf("\n");

    // 버튼에 'LED 토글' 기능 등록 후 여러 번 누르기
    register_button_callback(&toggle_led);
    simulate_button_press();
    simulate_button_press();
    simulate_button_press();

    return 0;
}