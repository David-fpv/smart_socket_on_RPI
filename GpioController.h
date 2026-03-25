#include <vector>
#include <string>
#include <errno.h>
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

class GpioController {
public:
    GpioController(std::string chip_path, std::vector<uint> gpio_lines, std::vector<enum gpiod_line_value> values, std::string consumer);
    ~GpioController();

    int init();
    int set_pin(uint gpio_line, enum gpiod_line_value value);

private:
    struct gpiod_line_request *request_ = NULL;
    std::string chip_path_; 
    std::vector<uint> gpio_lines_; 
    std::vector<enum gpiod_line_value> values_;  
    std::string consumer_;
};