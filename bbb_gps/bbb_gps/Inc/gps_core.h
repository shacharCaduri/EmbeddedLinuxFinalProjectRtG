#ifndef GPS_CORE_H_GPS_CORE_H_GPS_CORE_H
#define GPS_CORE_H_GPS_CORE_H_GPS_CORE_H
#include <main.h>
#include <stm32f7xx_hal.h>
#include "projdefs.h"

/**
 * @brief readable definition for the uart used for communicating BeagleBone
 */
#define BB_UART (&huart4)

/**
 * @brief extern to recognize uart handle defined (by default) in main.
 */
extern UART_HandleTypeDef huart4;

/**
 * @brief recv the data from the uart and store it the buffer given as parameter.
 *
 * @param[in,out] pData pointer / temp buffer to hold msg received.
 * @param[in] size the size in bytes to receive by UART.
 * @return status HAL_OK if all is good, HAL_ERROR otherwise.
 */
HAL_StatusTypeDef uart_recv(char *pData, size_t size);

/**
 * @brief send data got in param to uart.
 *
 * @param pData pointer to data to send.
 * @return status HAL_OK if all is good, HAL_ERROR otherwise.
 */
HAL_StatusTypeDef uart_send(char *pData, size_t size);

/**
 * @brief send the start/end message over uart.
 *
 * @param[in] msg pointer to the start/end message to send over uart.
 * @return status HAL_OK if all is good, HAL_ERROR otherwise.
 */
HAL_StatusTypeDef uart_send_msg(msg_st const * const msg);

/**
 * @brief waiting for start gps operation event from the bbb to start its operations.
 * @param[in,out] msg - pointer to msg indicating if the gps operation need to start, operations of
 * 		  			    the gps includes: send start / end message to bbb generate coords and
 * 		  			    unique id to send to the bbb.
 *
 * @return status HAL_OK if all is good, HAL_ERROR otherwise.
 */
 HAL_StatusTypeDef wait_start_gps_ops(msg_u8 *msg);

 /**
  * @brief build a start/end message to send later using the msg parameter
  *
  * @param[in,out] msg pointer to the message to store the data generated.
  * @param[in] msg_type the type of message to build, its either start / end messsage.
  * @return status HAL_OK if all is good, HAL_ERROR otherwise.
  */
HAL_StatusTypeDef build_msg(msg_st *msg, msg_u8 msg_type);

/**
 * @brief generate random coordinates (simulate gps function)
 *
 * @param[in,out] coords pointer to coord struct to store the generated coordinates into.
 * @return status HAL_OK if all is good, HAL_ERROR otherwise.
 */
HAL_StatusTypeDef generate_coords(coord_st *coords);

/**
 * @brief send the coordinates via uart (to beaglebone)
 *
 * @param[in] coords pointer to coords to send via uart.
 * @return status HAL_OK if all is good, HAL_ERROR otherwise.
 */
HAL_StatusTypeDef send_coords(coord_st const * const coords);

/**
 * @brief gps functionality start from here.
 *
 * @return status HAL_OK if all is good, HAL_ERROR otherwise.
 */
 HAL_StatusTypeDef gps_start(void);

#endif //GPS_CORE_H_GPS_CORE_H_GPS_CORE_H
