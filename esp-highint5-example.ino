#include <Arduino.h>

#define LED_BIT 2 // Built-in LED on GPIO 2
#define STROBE_BIT_n 39

void setup()
{
    Serial.begin(115200);

    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_DISABLE; // Disable GPIO interrupt
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED_BIT);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    io_conf.pin_bit_mask = (1ULL << STROBE_BIT_n);
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
    
    int INTR_NUM = 31; // extern level 5, see table in file soc.h for details
    ESP_INTR_DISABLE(INTR_NUM);
    intr_matrix_set(xPortGetCoreID(), ETS_GPIO_INTR_SOURCE, INTR_NUM);
    ESP_INTR_ENABLE(INTR_NUM);
    
    Serial.print("Level 5 Interrupt set on core ");
    Serial.println(xPortGetCoreID());
}

void loop()
{

}
