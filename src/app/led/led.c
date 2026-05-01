#include "stm32f4xx_hal.h"

void LED_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {0};
    gpio.Pin = GPIO_PIN_5;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA, &gpio);
}

void LED_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}