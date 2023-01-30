#include "../Inc/uart_utils.hpp"
#include "../Inc/projdefs.hpp"
#include "../Inc/bbb_gpio.hpp"

/**
 * @brief check if the button is pressed.
 */
bool uart_utils::is_btn_pressed(void) {
    BbbGpio gpio_input{"in"};
    
    while(true)  {
        int res = gpio_input.gpio_read();
        if(res == ERROR_MINUS_1)
            return false;

        if(res == true)
            break;
    }

    return true;
}


 /**
 * @brief start the process responsible for the UART operation,
 *        this operation handle communication over UART with STM32
 *        board which acting as the GPS of the beaglebone board.
 */ 
bool uart_utils::start_uart_process(void) {
    int pid = RESET_VAL;

    pid = fork();

    if(pid == RESET_VAL) {
        // init
        std::string device{UART_DEVICE};
        UartObj uart{device};

        std::cout << "UART handle child process start." << std::endl;
        
        if(!uart.uart_open())
            exit(EXIT_FAILURE);

        while(true) {
            bool status = RESET_VAL;               
            while(!(status = is_btn_pressed()));

            if(status == true) {
                std::string send_gps_msg{};
                send_gps_msg+=1;

                if(!uart.uart_send(send_gps_msg)) {
                    std::cerr << "UART send error" << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                exit(EXIT_FAILURE);
            }
        }

        if(!uart.uart_close())
            exit(EXIT_FAILURE);

        // child process finished
        std::cout << "child process finished" << std::endl;
        exit(EXIT_SUCCESS);        
    } else if (pid == ERROR_MINUS_1) { // if fork succeed.
        std::cerr << "fork syscall for UART child failed" << std::endl;
        return false;
    } else {
        return true;
    }
    // holding child for ever run.
    while(true);

    // if did not run forever it means error so return false
    return false;
}


/**
 * @brief Constructor for initializing the members needed for UART communication 
 */
uart_utils::UartObj::UartObj(std::string device) 
: device{device}, uart_fd(UART_ERROR) {
}

/**
 * @brief open the file for communicating over UART and configure the UART 
 *        with default configurations:
 *            baudrate: 115200,
 *            byte_size: 8,
 *            stop_bits: 1,
 *            parity: 0.
 */ 
bool uart_utils::UartObj::uart_open() {
    // Open the device file with the specified baudrate
    uart_fd = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if(uart_fd <= UART_ERROR) {
        std::cerr << "Failed to open " << device << std::endl;
        return false;
    }

    // Configurations
    struct termios options;
    tcgetattr(uart_fd, &options);
    // baudrate set for 115200 as shown. can be modify as user's wish. be careful as any changes can affect other parts of the project.
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD; 
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_fd, TCIFLUSH);
    tcsetattr(uart_fd, TCSANOW, &options);

    return true;
}

/**
 * @brief send data via uart
 */
bool uart_utils::UartObj::uart_send(std::string data) {
    int nbytes = RESET_VAL; // stores the number of bytes sent to UART.

    if (uart_fd <= UART_ERROR ) {
        std::cerr << "UART not open" << std::endl;
        return false;
    }

    if( (nbytes = write(uart_fd, (data.c_str()), data.size())) <= UART_ERROR ) {
        std::cerr << "UART error on send bytes" << std::endl;
        return false;
    }

    std::cout << "Send " << nbytes << " bytes over UART: " << data << std::endl;
    
    return true;
}


/**
 * @brief receive data via uart
 */
bool uart_utils::UartObj::uart_recv(std::string &data, const uint32_t size) {
    int nbytes = RESET_VAL; // stores the number of bytes received from UART.
    char buff[UART_MAX_RECV_BYTES] = {RESET_VAL};

    if (uart_fd <= UART_ERROR ) {
        std::cerr << "UART not open" << std::endl;
        return false;
    }

    if( (nbytes = read(uart_fd, buff, size)) <= UART_ERROR) {
        std::cerr << "UART error on receive bytes" << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief close uart file descriptor thus, close the UART communication.
 */
bool uart_utils::UartObj::uart_close() {
    if (uart_fd <= UART_ERROR) {
        std::cerr << "UART not open" << std::endl;
        return false;
    }

    if(close(uart_fd) <= UART_ERROR) {
        std::cerr << "UART error on close" << std::endl;
        return false;
    }

    std::cout << "UART closed." << std::endl;
    return true;
}

/** 
 * @brief Destruct the uart object byt closing the uart device communication. 
 */
uart_utils::UartObj::~UartObj() {
    if(uart_close())
        exit(EXIT_FAILURE);
}