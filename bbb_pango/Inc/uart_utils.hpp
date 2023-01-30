#ifndef DF026F62_7F57_4F1C_B5F0_7FA65D278D51
#define DF026F62_7F57_4F1C_B5F0_7FA65D278D51
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <fcntl.h>
#include <cstddef>
#include <unistd.h>
#include <termios.h>

namespace uart_utils {

/**
 * @brief maximum length for the device name string path name.
 */
static int constexpr MAX_DEVICE_PATH_NAME = 64;

/** @brief start bit definition for */
static int constexpr GPS_START_BIT = 1;

/**
 * @brief start the process responsible for the UART operation,
 *        this operation handle communication over UART with STM32
 *        board which acting as the GPS of the beaglebone board.
 * 
 * @return true for parent process when finished succefully, if
 *         child is exiting or fork did not succeed, return false.
 */
bool start_uart_process(void);

/**
 * @brief check if the button is pressed.
 * 
 * @return true if flag was raised (button pressed), false otherwise.
 */
bool is_btn_pressed(void);

/**
 * @brief waiting to receive GPS coordinates from STM32, wait until end
 *        message received otherwise would not continue.
 * 
 * @return true if finished succefully receiving the coordinates, false
 *         if did not received the messagese in the right order (i.e. 
 *         start message -> coordinates -> end message)
 */
bool recv_gps_coordinates(void);

/**
 * @brief class UartObj for creating UART object to start communicating over UART
 */
class UartObj {
private:
    /** @brief compilation time error value define for uart file descriptor / bytes received or sent */
    static int constexpr UART_ERROR = -1;

    /** @brief value for maximum recv bytes in one call for read function */
    static int constexpr UART_MAX_RECV_BYTES = 256;

    /** @brief UART device file path */
    std::string device; 
    
    /** @brief File Descriptor for reading/writing */
    int uart_fd; 

public:
    /**
     * @brief Constructor for initializing the members needed for UART communication 
     * 
     * @param[in] device name of the uart device to open for communication.
     */
    UartObj(std::string device);
    
    /** @brief Destruct the uart object byt closing the uart device communication. */
    ~UartObj();
    
    /**
     * @brief open the file for communicating over UART and configure the UART 
     *        with default configurations:
     *            baudrate: 115200,
     *            byte_size: 8,
     *            stop_bits: 1,
     *            parity: 0.
     * 
     * @return true if succeed openning, false otherwise.
     */
    bool uart_open();

    /**
     * @brief send data via uart
     * 
     * @param[in] data send this data to uart into. 
     * @return true if succefully send any bytes (zero included), false file was not opened 
     *         or some error upon sending ( bytes sent < 0) 
     */
    bool uart_send(std::string data);

    /**
     * @brief receive data via uart
     * 
     * @param[in,out] data receive the data from uart into this referenced buffer called data. 
     * @param[in] size the number of bytes expecting to receive from UART.
     * @return true if succefully receive any bytes (zero included), false file was not opened 
     *         or received some error ( bytes received < 0) 
     */
    bool uart_recv(std::string &data, const uint32_t size);

    /**
     * @brief close uart file descriptor thus, close the UART communication.
     * 
     * @return true if succeed closing, false otherwise. 
     */
    bool uart_close();
};

}

#endif /* DF026F62_7F57_4F1C_B5F0_7FA65D278D51 */
