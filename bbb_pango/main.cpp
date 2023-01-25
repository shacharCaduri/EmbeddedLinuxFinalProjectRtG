#include <iostream>
#include <iomanip> // manipulators for std::cout
#include <cstdlib> // (EXIT_SUCCESS = 0), (EXIT_FAILURE = 1), exit()
#define ARGC_NUM 0
using namespace std; // using the namespace std so std:: would not be needed. <example: instead of std::cout --> cout, std::endl --> endl, etc..>

/**
 * @brief main entry of the application
 * @param[in] argc number of arguments to main
 * @param[in] argv array of pointers to char hold the inputs of the programs.
 * @return status code indicate if application failed or succeed.
 */
int main(int argc, char *argv[]) {
    if(argc != ARGC_NUM) return EXIT_FAILURE;
    return EXIT_SUCCESS; 
}