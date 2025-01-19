#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

//Dimensões do teclado
#define LINHA_QNTD 4
#define COLUNA_QNTD 4

//Definição dos pinos dos LEDs e buzzer
#define GPIO_VERDE 11
#define GPIO_AZUL 12
#define GPIO_VERMELHO 13
#define GPIO_BUZZER 21

//Definição dos pinos do teclado
const uint gpioCol[COLUNA_QNTD] = {4, 3, 2, 1};
const uint gpioLinha[LINHA_QNTD] = {8, 7, 6, 5};

//Mapeamento das teclas
const char teclado[COLUNA_QNTD][LINHA_QNTD] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

//Configuração das portas GPIO dos periféricos
void init_gpio()
{
    for (int i = 0; i < LINHA_QNTD; i++)
    {
        gpio_init(gpioLinha[i]);
        gpio_set_dir(gpioLinha[i], GPIO_OUT);
        gpio_put(gpioLinha[i], 1);
    }

    for (int i = 0; i < COLUNA_QNTD; i++)
    {
        gpio_init(gpioCol[i]);
        gpio_set_dir(gpioCol[i], GPIO_IN);
        gpio_pull_up(gpioCol[i]);
    }

    gpio_init(GPIO_VERMELHO);
    gpio_init(GPIO_VERDE);
    gpio_init(GPIO_AZUL);
    gpio_init(GPIO_BUZZER);

    gpio_set_dir(GPIO_VERMELHO, GPIO_OUT);
    gpio_set_dir(GPIO_VERDE, GPIO_OUT);
    gpio_set_dir(GPIO_AZUL, GPIO_OUT);
    gpio_set_dir(GPIO_BUZZER, GPIO_OUT);
    gpio_set_function(GPIO_BUZZER, GPIO_FUNC_PWM); // setta a função PWM para o  Buzzer
}

//Detectar, por linha e coluna, a tecla pressionada 
char escanear_teclado()
{
    for (int row = 0; row < LINHA_QNTD; row++)
    {
        gpio_put(gpioLinha[row], false);

        for (int col = 0; col < COLUNA_QNTD; col++)
        {
            if (!gpio_get(gpioCol[col]))
            {
                gpio_put(gpioLinha[row], true);
                return teclado[row][col];
            }
        }
        gpio_put(gpioLinha[row], true);
    }
    return 0; // Nenhuma tecla detectada
}

// Toca uma frequência no buzzer, usando o PWM
void play_tone(uint16_t frequency, uint duration_ms, uint pin) {
    if (frequency > 0) {
        uint slice_num = pwm_gpio_to_slice_num(pin);
        pwm_set_wrap(slice_num, 125000000 / frequency - 1);
        pwm_set_gpio_level(pin, (125000000 / frequency) / 2);
        pwm_set_enabled(slice_num, true);
        sleep_ms(duration_ms);
    }
    else {
        pwm_set_enabled(pwm_gpio_to_slice_num(pin), false);
    }
}

//Realiza ação de acordo com a tecla pressionada
void executar_tecla(char teclaPressionada)
{
    switch (teclaPressionada)
    {
    case 'A': //Liga o LED vermelho
        gpio_put(GPIO_VERMELHO, true);
        sleep_ms(1000);
        gpio_put(GPIO_VERMELHO, false);
        break;
    case 'B': //Liga o LED verde
        gpio_put(GPIO_VERDE, true);
        sleep_ms(1000);
        gpio_put(GPIO_VERDE, false);
        break;
    case 'C': //Liga o LED Azul
        gpio_put(GPIO_AZUL, true);
        sleep_ms(1000);
        gpio_put(GPIO_AZUL, false);
        break;
    case 'D': //Liga os três LEDS
        gpio_put(GPIO_VERMELHO, true);
        gpio_put(GPIO_VERDE, true);
        gpio_put(GPIO_AZUL, true);
        sleep_ms(1000);
        gpio_put(GPIO_VERMELHO, false);
        gpio_put(GPIO_VERDE, false);
        gpio_put(GPIO_AZUL, false);
        break;
    case '#': // Liga três LEDs alternadamente
        gpio_put(GPIO_VERDE, true);
        sleep_ms(500);
        gpio_put(GPIO_VERDE, false);
        gpio_put(GPIO_AZUL, true);
        sleep_ms(500);
        gpio_put(GPIO_AZUL, false);
        gpio_put(GPIO_VERMELHO, true);
        sleep_ms(500);
        gpio_put(GPIO_VERMELHO, false);
        break;
    case '*': // ativa o buzzer
        int tones[] = {
            2093, 2350, 2637, 2794, 3136, 3520, 3951, 4186, 0 // dó, ré, mi, fá, sol, lá, si, DÓ, pausa
        };
        int leds_to_lightup[] = {
            GPIO_VERMELHO,
            GPIO_AZUL,
            GPIO_VERDE,
            GPIO_VERMELHO,
            GPIO_AZUL,
            GPIO_VERDE,
            GPIO_VERMELHO,
            GPIO_AZUL
        }; // um led para cada nota
        int tam_tones = 9;
        for (int i = 0; i < tam_tones; i++) {
            if (tones[i] != 0)
                gpio_put(leds_to_lightup[i], true);
            play_tone(tones[i], 500, GPIO_BUZZER);
            if (tones[i] != 0)
                gpio_put(leds_to_lightup[i], false);
        }
        break;
    default: //Caso nenhuma tecla seja pressionada, não faz nada
        break;
    }
}

int main()
{
    stdio_init_all();
    init_gpio();

    while (true)
    {
        char teclaPressionada = escanear_teclado();
        executar_tecla(teclaPressionada);
        sleep_ms(100);
    }
}