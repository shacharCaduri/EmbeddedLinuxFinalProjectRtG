#include "../Inc/bbb_gpio.hpp"

    /**
     * @brief Constructor
     *        Exports the GPIO pin, sets the direction to input (in) / output (out)
    */
    BbbGpio::BbbGpio(std::string const &direction) {
        // Export the GPIO pin
        std::ofstream export_file("/sys/class/gpio/export");
        export_file << kGpioPin;
        export_file.close();

        // Set the GPIO direction to input
        std::ofstream direction_file("/sys/class/gpio/gpio67/direction");
        if (direction == "in") {
            direction_file << direction;
        } else {
            direction_file << "out";
        }
        direction_file.close();
    }

    /**
     * @brief Read the value of the GPIO pin
    */
    int BbbGpio::gpio_read() {
        // Open the value file
        std::ifstream value_file{"/sys/class/gpio/gpio67/value", std::ios::in};
        if (!value_file.is_open()) {
            std::cerr << "Failed to open value file for reading" << std::endl;
            return ERROR_MINUS_1;
        }

        // Read the value
        std::string value_str;
        std::getline(value_file, value_str);
        value_file.close();

        // Return true if the value is 1, false otherwise
        return value_str == "1";
    }

    /**
     * @brief Destructor
     *
     * Unexports the GPIO pin
     */
    BbbGpio::~BbbGpio() {
        // Unexport the GPIO pin
        std::ofstream unexport_file("/sys/class/gpio/unexport");
        unexport_file << kGpioPin;
        unexport_file.close();
    }