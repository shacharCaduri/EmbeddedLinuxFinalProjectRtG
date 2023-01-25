#ifndef PROJDEFS_H_PROJDEFS_H_PROJDEFS_H
#define PROJDEFS_H_PROJDEFS_H_PROJDEFS_H

/** @brief zero value for resetting / init variables and other objects, instead of NULL which cast to void* */
#define RESET_VAL 0

/** @brief true value for booleans */
#define TRUE 1

/** @brief false value for booleans */
#define FALSE 0

/** @brief the start msg bit to set in which indicate the message to send is either a start / end message */
#define START_MSG 1

/** @brief the end msg bit to set in which indicate the message to send is either a start / end message */
#define END_MSG 0

/** @brief max size (in bytes) for the buffer that stores the coordinates to send / receive to / from uart */
#define MAX_COORD_MSG_SIZE sizeof(coord_st)

/** @brief max size (in bytes) for the buffer that stores the messages to send / receive to / from uart */
#define MAX_MSG_SIZE sizeof(msg_st)

/**
 * @brief indicate the gps is on, the gps start its operation: generate coords, unique id, send
 * 		  start / end messages.
 */
#define U8_GPS_OP_ON (uint8_t)1

/**
 * @brief alias for uint8_t minimal memory consume for binary value indicate the user
 *        the value is for messages.
 */
typedef uint8_t msg_u8;

#pragma pack(1) // set packing for 1 byte each, no padding in structs.
/**
 * @brief struct coordinate to send
 */
typedef struct coordinate {
	int x;
	int y;
}coord_st;

/**
 * @brief struct start/end message + uniqueID, start/end msgType is a binary value (using bitwise)
 *        either start/end. start = 1, end = 0.
 */
typedef struct message {
	msg_u8 msg:1; //used bit field to ensure boolean value.
	uint32_t uID;
}msg_st;

#pragma pack(0) // end of pragma pack(1), return to the original packing

#endif //PROJDEFS_H_PROJDEFS_H_PROJDEFS_H
