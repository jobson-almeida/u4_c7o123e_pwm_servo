#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define SERVO_GPIO 22
#define FREQ_PWM 50.0f

int main()
{
    stdio_init_all();

    gpio_set_function(SERVO_GPIO, GPIO_FUNC_PWM);       // define a função do pino 22 como saida PWM
    uint slice_num = pwm_gpio_to_slice_num(SERVO_GPIO); // determina a slice que controla a GPIO recém definida
    float freq_clk_sys = clock_get_hz(clk_sys);         // retorna a frequencia de clock do sistema (Hz)

    // contatdor - também conhecimo com o TOP
    uint16_t wrap = 9950; // - melhor ajuste até o momento ajustado e experimentado

    float divider = freq_clk_sys / (50.0f * (wrap + 1)); // define frequência de 50Hz e o divisor do clock
    pwm_set_clkdiv(slice_num, divider);                  // aplica o divisor
    pwm_set_wrap(slice_num, wrap);                       // aplica o wrap
    pwm_set_enabled(slice_num, true);

    // DEBUGGING
    // printf("%d\n", wrap);
    // printf("%f\n", divider);

    // uint16_t freq_pwm_calculate = freq_clk_sys / ((divider + 0 / 16) * wrap); DEBUGGING
    // printf("%d\n", freq_pwm_calculate);

    // uint16_t wrap_calculate = (freq_clk_sys * (divider + 0 / 16)) / FREQ_PWM; // DEBBUGING: valor funcional mas não ajustado
    // printf("%d\n", wrap_calculate);



    uint16_t starting_position = 260; // variável auxiliar que reperesenta a posição inicial dos ciclos - valor experimentado e ajustado
    int step_size = 10; // passo de incremento
    int level = starting_position; 
    uint16_t level_current = starting_position;

    // ciclo de trabalho
    uint16_t degrees180 = (uint16_t)(0.12 * (wrap + 1)); // 180 graus
    uint16_t degrees90 = (uint16_t)(0.0735 * (wrap + 1)); // 90 graus

    sleep_ms(100); // pausa para reposicionamento do servo motor 

    // ciclo de 0 -> 180 graus
    for (uint16_t level = degrees90; level <= degrees180; level += step_size)
    {
        pwm_set_chan_level(slice_num, PWM_CHAN_A, level);
        // printf("%d\n", level);
        level_current = level;
        sleep_ms(5);
    }
    sleep_ms(5000);

    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
