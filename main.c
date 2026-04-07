#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdbool.h>

#define INPUT 19

enum{LO, HI};

void app_main(void)
{
    //configure the INPUT pin 
    gpio_config_t button = 
    {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << INPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE
    };
    gpio_config(&button); //Configure GPIO's Mode,pull-up,PullDown,IntrType

    bool button_state = HI;

    static const char *TAG = "GPIO_learn";/*The static keyword limits the 
                                    symbol’s visibility to the current file, 
                                    while const ensures the string is stored 
                                    in read-only memory instead of consuming RAM.*/


    while(1)
    {
        button_state = gpio_get_level(INPUT);
        if(button_state == HI)
        {
            ESP_LOGI(TAG,"button state = %d\n", button_state);
        }
        else if(button_state == LO)
        {
            ESP_LOGI(TAG,"button state = %d\n", button_state);
        }

        vTaskDelay(pdMS_TO_TICKS(200)); // required to avoid WDT timeout

    }

}
/*Output
I (31075) GPIO_learn: button state = 0

I (31275) GPIO_learn: button state = 0

I (31475) GPIO_learn: button state = 0

I (31675) GPIO_learn: button state = 1

I (31875) GPIO_learn: button state = 1

I (32075) GPIO_learn: button state = 1*/
