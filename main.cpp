#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "GpioController.h"

int main() {

    std::string chip_path = "/dev/gpiochip0";
	std::vector<uint> gpio_lines = { 26, 20, 21 };
	std::vector<enum gpiod_line_value> values = { 
        GPIOD_LINE_VALUE_ACTIVE,
		GPIOD_LINE_VALUE_ACTIVE,
		GPIOD_LINE_VALUE_INACTIVE
    };
    std::string consumer_gpio = "toggle-multiple-line-values";

    GpioController gpio_controller(chip_path, gpio_lines, values, consumer_gpio);
    gpio_controller.init();

    for (;;) {
        sleep(1);
        gpio_controller.set_pin(20, GPIOD_LINE_VALUE_ACTIVE);
        gpio_controller.set_pin(21, GPIOD_LINE_VALUE_ACTIVE);
        gpio_controller.set_pin(26, GPIOD_LINE_VALUE_ACTIVE);

        sleep(1);
        gpio_controller.set_pin(20, GPIOD_LINE_VALUE_INACTIVE);
        gpio_controller.set_pin(21, GPIOD_LINE_VALUE_INACTIVE);
        gpio_controller.set_pin(26, GPIOD_LINE_VALUE_INACTIVE);
    }

    return 0;
}