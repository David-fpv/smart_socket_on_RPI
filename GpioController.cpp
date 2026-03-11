#include "GpioController.h"

GpioController::GpioController(std::string chip_path, std::vector<uint> gpio_lines, std::vector<enum gpiod_line_value> values, std::string consumer) {
	chip_path_ = chip_path;
	gpio_lines_ = gpio_lines;
	values_ = values;
	consumer_ = consumer;
}

int GpioController::init()
{
    struct gpiod_request_config *rconfig = NULL;
	struct gpiod_line_settings *settings;
	struct gpiod_line_config *lconfig;
	struct gpiod_chip *chip;
	unsigned int i;
	int ret;

	chip = gpiod_chip_open(chip_path_.c_str());
	if (!chip)
		return EXIT_FAILURE;

	settings = gpiod_line_settings_new();
	if (!settings)
		goto close_chip;

	gpiod_line_settings_set_direction(settings,
					  GPIOD_LINE_DIRECTION_OUTPUT);

	lconfig = gpiod_line_config_new();
	if (!lconfig)
		goto free_settings;

	for (i = 0; i < gpio_lines_.size(); i++) {
		ret = gpiod_line_config_add_line_settings(lconfig, &gpio_lines_[i],
							  1, settings);
		if (ret)
			goto free_line_config;
	}

	for (i = 0; i < gpio_lines_.size(); i++) {
		ret = gpiod_line_config_add_line_settings(lconfig, &gpio_lines_[i], 1, settings);
	}

	if (consumer_.c_str()) {
		rconfig = gpiod_request_config_new();
		if (!rconfig)
			goto free_line_config;

		gpiod_request_config_set_consumer(rconfig, consumer_.c_str());
	}

	request_ = gpiod_chip_request_lines(chip, rconfig, lconfig);

	gpiod_request_config_free(rconfig);

free_line_config:
	gpiod_line_config_free(lconfig);

free_settings:
	gpiod_line_settings_free(settings);

close_chip:
	gpiod_chip_close(chip);

	if (request_ == NULL) {
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
};

GpioController::~GpioController()
{
    gpiod_line_request_release(request_);
};

int GpioController::set_pin(int gpio_line, enum gpiod_line_value value)
{
	//std::cout << "Gpio line " << pin << " = " << value_str(value) << std::endl;
	bool flag = 0;
	for(int i = 0; i < gpio_lines_.size(); i++) {
		if (gpio_lines_.at(i) == gpio_line) {
			flag = 1;
			break;
		}
	}

	if (flag == 0) {
		return EXIT_FAILURE;
	}
	
	gpiod_line_request_set_value(request_, gpio_line, value);
	return EXIT_SUCCESS;
};

