#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"


#define SERVO_GPIO 22
#define FREQ_PWM 50.0f

int main()
{
    stdio_init_all();
 
    gpio_set_function(SERVO_GPIO, GPIO_FUNC_PWM); // define a função do pino 22 como saida PWM
    uint slice_num = pwm_gpio_to_slice_num(SERVO_GPIO); // determina a slice que controla a GPIO recém definida
    float freq_clk_sys = clock_get_hz(clk_sys); // retorna a frequencia de clock do sistema (Hz)

    // contatdor - também conhecimo com o TOP
    uint16_t wrap = 58304; // - melhor ajuste até o momento ajustado e experimentado

    float divider = freq_clk_sys / (50.0f * (wrap + 1)); // define frequência de 50Hz e o divisor do clock
    pwm_set_clkdiv(slice_num, divider);                  // aplica o divisor
    pwm_set_wrap(slice_num, wrap);                       // aplica o wrap
    pwm_set_enabled(slice_num, true);  
    
    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
