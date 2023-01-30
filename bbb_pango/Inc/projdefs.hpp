#ifndef D179CA7B_7616_48BC_B952_14C839361741
#define D179CA7B_7616_48BC_B952_14C839361741

/** @brief reset value for initializing any object / variable / array with zero/es */
#define RESET_VAL 0

/** @brief error value for some lib functions such as fork(), and etc.. */
#define ERROR_MINUS_1 -1

/** @brief the UART device to communicate with */
#define UART_DEVICE "/dev/ttyS4"

/**
 * @brief the exported file to write to so the kernel can export 
 *        the control of the pin to user space. 
 */
#define GPIO_EXPORT "/sys/class/gpio/export"

/**
 * @brief the unexported file to write to so the kernel can unexport 
 *        the control of the pin from user space. 
 */
#define GPIO_UNEXPORT "/sys/class/gpio/unexport"

/** @brief the specific GPIO path to act as a button */
#define BUTTON_GPIO_PATH "/sys/class/gpio/gpio66"

/** @brief the specific GPIO to act as a button */
#define BUTTON_GPIO "66"

/** @brief the specific GPIO path to act as a button */
#define BUTTON2_GPIO_PATH "/sys/class/gpio/gpio67"

/** @brief the specific GPIO to act as a button */
#define BUTTON2_GPIO "67"

#endif /* D179CA7B_7616_48BC_B952_14C839361741 */
