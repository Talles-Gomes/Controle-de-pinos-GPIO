#include <stdio.h>
#include "pico/stdlib.h"

const uint Buzzer = 21;
const uint led_G = 11;
const uint led_B = 12;
const uint led_R = 13;
#define cols 4
#define rows 4
#define Tempo_led 500

// função de acender e apagar os leds
int acender_led(uint led)
{
    gpio_put(led, 1);
    sleep_ms(Tempo_led);
    gpio_put(led, 0);
}
// função de inicialização dos leds
void led_init()
{
    gpio_init(led_G);
    gpio_set_dir(led_G, GPIO_OUT);

    gpio_init(led_B);
    gpio_set_dir(led_B, GPIO_OUT);

    gpio_init(led_R);
    gpio_set_dir(led_R, GPIO_OUT);
}
// função de leitura do teclado
const uint8_t row_pins[rows] = {8, 7, 6, 5};  // R1 R2 R3 R4
const uint8_t col_pins[cols] = {4, 3, 2, 28}; // C1 C2 C3 C4
// mapamento teclado matricial
const char key_map[rows][cols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
// inicializacao do teclao
void keypad_init()
{
    for (int i = 0; i < rows; i++)
    {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], false);
    }
    for (int i = 0; i < cols; i++)
    {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_down(col_pins[i]);
    }
}
// função de acionamento do buzzer
void acionar_buzzer()
{
    // tempo de acionamento do buzzer
    int time = 1000;
    // executa enquanto o contador não zera
    while (time > 0)
    {
        // ativa o buzzer
        gpio_put(Buzzer, 1);
        // fica ativo por 1 ms
        sleep_ms(1);
        // decrementa contador
        time -= 1;
        // desativa o buzzer
        gpio_put(Buzzer, 0);
        // fica desativado por 3 ms
        sleep_ms(3);
        // decrementa contador
        time -= 3;
    }
}

int main()
{
    // inicialização das portas com os pinos e o buzzer
    led_init();
    stdio_init_all();
    // inicialização do teclado
    keypad_init();
    
    gpio_init(Buzzer);
    gpio_set_dir(Buzzer, GPIO_OUT);

    printf("Sistema inicializado. Pressione uma tecla.\n");

    while (true)
    {
        // definir os valores para comparação

        // ler o teclado e fazer os comparativos

        // FAVOR EXCLUIR OS COMENTÁRIOS ABAIXO ANTES DE ENVIAR O CÓDIGO
        // para acionar os leds deve usar a função acender_led(led) passando o led que deseja acionar
        // exemplo: acender_led(led_G); acende o led verde,
        // acender_led(led_B); acende o led azul,
        // acender_led(led_R); acende o led vermelho

        // acender o led de acordo com o valor do teclado

        // Lê a tecla pressionada
        char key = read_keypad();

        if (key != '\0') // Verifica se alguma tecla foi pressionada
        {
            printf("Tecla pressionada: %c\n", key);

            // Acionamento dos LEDs com base no valor pressionado
            switch (key)
            {
            case '1':
                acender_led(led_G); // Acende o LED verde
                break;
            case '2':
                acender_led(led_B); // Acende o LED azul
                break;
            case '3':
                acender_led(led_R); // Acende o LED vermelho
                break;
            case 'A':
                acionar_buzzer(); // Aciona o buzzer
                break;
            default:
                printf("Tecla sem função associada.\n");
                break;
            }
        }
        sleep_ms(100); // Pequena pausa para evitar leituras repetidas
    }
}
