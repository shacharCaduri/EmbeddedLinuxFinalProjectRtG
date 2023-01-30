#include <iostream>
#include <iomanip> // manipulators for std::cout
#include <cstdlib> // (EXIT_SUCCESS = 0), (EXIT_FAILURE = 1), exit()
#include <unistd.h> // fork
#include "Inc/uart_utils.hpp" // uart operations
#include "Inc/projdefs.hpp" // all projdefs
#define ARGC_NUM 1
using namespace std; // using the namespace std so std:: would not be needed. <example: instead of std::cout --> cout, std::endl --> endl, etc..>

/**
 * @brief main entry of the application
 * @param[in] argc number of arguments to main
 * @param[in] argv array of pointers to char hold the inputs of the programs.
 * @return status code indicate if app  lication failed or succeed.
 */
int main(int argc, char *argv[]) {
    if(argc != ARGC_NUM) return EXIT_FAILURE;
    int check;
    if(check = uart_utils::start_uart_process()) {
        std::cout << "main work" << std::endl;
        while(true);
    } else {
        return EXIT_FAILURE;
    }
    if(check == 1)
        std::cout << "process main finish" << std::endl;
    return EXIT_SUCCESS; 
}