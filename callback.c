#include <stdio.h>

// --- LED ���� �Լ��� (���� �ݹ��� �� �Լ���) ---

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
    // led_state�� �Լ��� ������ ���� ����ؾ� �ϹǷ� static���� ����
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

// --- ��ư ����̹� (�ݹ� �ý���) ---

// ��ϵ� �ݹ� �Լ��� ������ �Լ� ������. '�����' ����.
void (*g_button_callback)(void) = NULL;

// ������ �Լ�(�ݹ�)�� �ý��ۿ� ����ϴ� �Լ�
// '�Լ� ������'�� ���ڷ� ����
void register_button_callback(void (*callback_to_register)(void))
{
    g_button_callback = callback_to_register;
    printf(">> ���ο� ����� ��ư�� ��ϵǾ����ϴ�.\n");
}

// ��ư�� ������ �̺�Ʈ�� �ùķ��̼�
void simulate_button_press(void)
{
    printf("��ư ����! ");
    // ��ϵ� �ݹ� �Լ��� �ִ��� Ȯ���ϰ�, �ִٸ� ȣ���Ѵ�.
    if (g_button_callback != NULL)
    {
        g_button_callback(); // �ݹ� ȣ��!
    }
    else
    {
        printf("�ƹ� ��ɵ� ��ϵ��� ����.\n");
    }
}

// --- ���� �Լ� (�ó�����) ---

int main(void)
{
    // ��ư�� 'LED �ѱ�' ��� ��� �� ������
    register_button_callback(&turn_led_on);
    simulate_button_press();

    printf("\n");

    // ��ư�� 'LED ���' ��� ��� �� ���� �� ������
    register_button_callback(&toggle_led);
    simulate_button_press();
    simulate_button_press();
    simulate_button_press();

    return 0;
}