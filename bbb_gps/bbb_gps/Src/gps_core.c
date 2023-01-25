/*
 * gps_core.c
 *
 *  Created on: Jan 24, 2023
 *      Author: shach
 */
#include "gps_core.h"
#include "inttypes.h" // for uint8_t
#include "string.h" // for memcpy
#include "stdlib.h" // rand, srand
#include "time.h" // time

/**
 * @brief gps functionality start from here.
 */
HAL_StatusTypeDef gps_start(void) {
	//init stack variables
	msg_u8 start_gps_op_u8msg = RESET_VAL; //holding msg received from bbb to start gps op.
	HAL_StatusTypeDef status = HAL_ERROR; // status for the functions HAL_OK / HAL_ERROR
	msg_st msg = { RESET_VAL }; // msg struct store start/end messages.
	coord_st coords = { RESET_VAL }; // coord struct to store coordinate generated.
	srand(time(NULL)); // Initialization for random generator, should only be called once.

	// life loop of gps functionality,
	// NOTE: must not get out of this while loop while system is on.
	while (TRUE) {
		//wait and check if need to start. synchronous waiting
		if ((status = wait_start_gps_ops(&start_gps_op_u8msg)) != HAL_OK)
			break;

		if (start_gps_op_u8msg == U8_GPS_OP_ON) {
			if(build_msg(&msg, START_MSG) != HAL_OK) // build the relevant msg to send
				break;

			if (uart_send_msg(&msg) != HAL_OK)
				break;

			if(generate_coords(&coords) != HAL_OK)
				break;

			if(send_coords(&coords) != HAL_OK)
				break;

			if(build_msg(&msg, END_MSG) != HAL_OK) // build the relevant msg to send
				break;

			if (uart_send_msg(&msg) != HAL_OK)
				break;
		}
	}

	if (status == HAL_ERROR) {
		while (TRUE) {
			//error fault similar to hard fault.
		};
	}

	return status;
}

/**
 * @brief synchronous waiting for start gps operation event from the bbb to start its operations
 */
HAL_StatusTypeDef wait_start_gps_ops(msg_u8 *msg) {
	if( msg == NULL )
		return HAL_ERROR;

	char stored_data[MAX_MSG_SIZE] = { RESET_VAL };

	while (TRUE) {
		if (uart_recv(stored_data, sizeof(*msg)) != HAL_OK)
			return HAL_ERROR;

		memmove(msg, stored_data, sizeof(*msg));

		if (*msg == U8_GPS_OP_ON)
			break;
	}

	return HAL_OK;
}

/**
 * @brief recv the data from the uart and store it the buffer given as parameter.
 */
HAL_StatusTypeDef uart_recv(char *pData, size_t size) {
	if( pData == NULL )
		return HAL_ERROR;

	if (HAL_UART_Receive(BB_UART, (uint8_t*) pData, size, HAL_MAX_DELAY) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

/**
 * @brief send data got in param to uart.
 */
HAL_StatusTypeDef uart_send(char *pData, size_t size) {
	if( pData == NULL )
		return HAL_ERROR;

	if (HAL_UART_Transmit(BB_UART, (uint8_t*) pData, size, HAL_MAX_DELAY) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

/**
 * @brief send the start/end message over uart.
 *
 * @param[in] msg the start/end message to send over uart.
 * @return status HAL_OK if all is good, HAL_ERROR otherwise.
 */
HAL_StatusTypeDef uart_send_msg(msg_st const *const msg) {
	if( msg == NULL )
		return HAL_ERROR;

	char data[MAX_MSG_SIZE] = {RESET_VAL};

	memmove(data, msg, sizeof(data));

	if (uart_send(data, sizeof(data)) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

/**
 * @brief build a start/end message to send later using the msg parameter
 */
HAL_StatusTypeDef build_msg(msg_st *msg, msg_u8 msg_type) {
	if (msg == NULL)
		return HAL_ERROR;

	static uint32_t uID = RESET_VAL;

	if (msg_type != START_MSG || msg_type != END_MSG)
		return HAL_ERROR;

	msg->msg = msg_type;
	msg->uID = uID++;

	return HAL_OK;
}

/**
 * @brief generate random coordinates (simulate gps function)
 */
HAL_StatusTypeDef generate_coords(coord_st *coords) {
	if (coords == NULL)
		return HAL_ERROR;

	int rand_x = RESET_VAL, rand_y = RESET_VAL;

	rand_x = rand() % RAND_MAX, rand_y = rand() % RAND_MAX;

	coords->x = rand_x;
	coords->y = rand_y;

	return HAL_OK;
}

/**
 * @brief send the coordinates via uart (to beaglebone)
 */
HAL_StatusTypeDef send_coords(coord_st const * const coords) {
	if(coords == NULL)
		return HAL_ERROR;

	char data[MAX_COORD_MSG_SIZE] = {RESET_VAL};

	memmove(data, coords, sizeof(data));

	if(uart_send(data, sizeof(data)) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

