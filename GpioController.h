#include <vector>
#include <errno.h>
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

class GpioController {
public:
    GpioController(const char *chip_path, const unsigned int *gpio_lines, enum gpiod_line_value *values, unsigned int num_lines,
		     const char *consumer);
    ~GpioController();

    int init();
    int set_pin(int gpio_line, enum gpiod_line_value values);

private:
    struct gpiod_line_request *request_ = NULL;
    const char *chip_path_; 
    const unsigned int *gpio_lines_; 
    enum gpiod_line_value *values_; 
    unsigned int num_lines_; 
    const char *consumer_;
};