#ifndef D2500658_0778_4FB8_8DFC_7D9E02370FC2
#define D2500658_0778_4FB8_8DFC_7D9E02370FC2

#include "projdefs.hpp"
#include <fstream>
#include <iostream>

/**
 * @class BbbGpio
 * @brief Class for interacting with a GPIO pin on the BeagleBone Black
 */
class BbbGpio {
private:
    /** @brief The GPIO pin number */
    static constexpr int kGpioPin = 67;
    /** @brief The path to the GPIO export file */
    static constexpr char kGpioExportPath[] = "/sys/class/gpio/export";
    /** @brief The path to the GPIO direction file */
    static constexpr char kGpioDirectionPath[] = "/sys/class/gpio/gpio67/direction";
    /** @brief The path to the GPIO value file */
    static constexpr char kGpioValuePath[] = "/sys/class/gpio/gpio67/value";
    
public:
    /**
     * @brief Constructor
     *        Exports the GPIO pin, sets the direction to input (in) / output (out)
     * 
     * @param[in] direction the direction of the GPIO, out / in
     */
    BbbGpio(std::string const &direction);

    /**
     * @brief Read the value of the GPIO pin
     *
     * @return true if the pin is high, false low, error_value -1 for errors
     */
    int gpio_read();

    /**
     * @brief Destructor
     *
     * Unexports the GPIO pin
     */
    ~BbbGpio();
};
#endif /* D2500658_0778_4FB8_8DFC_7D9E02370FC2 */
