#include <iostream>
using namespace std;

#include "GpioController.h"

int main() {

    static const char *const chip_path = "/dev/gpiochip0";
    const int NUM_LINES = 3;
	static const unsigned int gpio_lines[NUM_LINES] = { 26, 20, 21 };

	enum gpiod_line_value values[NUM_LINES] = { 
        GPIOD_LINE_VALUE_ACTIVE,
		GPIOD_LINE_VALUE_ACTIVE,
		GPIOD_LINE_VALUE_INACTIVE
    };

    GpioController gpio_controller(chip_path, gpio_lines, values, NUM_LINES, "toggle-multiple-line-values");
    gpio_controller.init();

    for (;;) {
        sleep(1);
        gpio_controller.set_pin(20, GPIOD_LINE_VALUE_ACTIVE);

        sleep(1);
        gpio_controller.set_pin(20, GPIOD_LINE_VALUE_INACTIVE);
    }

    return 0;
}