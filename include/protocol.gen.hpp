#include <Arduino.h>

// PROTOCOL (frame_id, param_length, [params sizes]) --> generated with Python
const uint8_t PING[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t PONG[] = {1, 2, 1, 1, 0, 0, 0, 0, 0, 0};
const uint8_t SET_SPEED[] = {4, 3, 2, 2, 2, 0, 0, 0, 0, 0};
const uint8_t STM_CODER_DATA[] = {5, 2, 2, 2, 0, 0, 0, 0, 0, 0};
const uint8_t SET_STM_MODE[] = {7, 1, 1, 0, 0, 0, 0, 0, 0, 0};
const uint8_t GO_TO_ANGLE[] = {8, 4, 2, 2, 2, 1, 0, 0, 0, 0};
const uint8_t GO_TO[] = {9, 3, 2, 2, 1, 0, 0, 0, 0, 0};
const uint8_t ROTATE[] = {10, 1, 2, 0, 0, 0, 0, 0, 0, 0};
const uint8_t SET_LEFT_PID[] = {12, 3, 2, 2, 2, 0, 0, 0, 0, 0};
const uint8_t SET_RIGHT_PID[] = {13, 3, 2, 2, 2, 0, 0, 0, 0, 0};
const uint8_t SET_BOTH_PID[] = {14, 3, 2, 2, 2, 0, 0, 0, 0, 0};
const uint8_t SET_PWM[] = {15, 2, 2, 2, 0, 0, 0, 0, 0, 0};
const uint8_t SET_POSITION[] = {16, 3, 2, 2, 2, 0, 0, 0, 0, 0};
const uint8_t SET_STM_PARAM[] = {17, 3, 2, 2, 2, 0, 0, 0, 0, 0};
const uint8_t CURRENT_POS[] = {18, 3, 2, 2, 2, 0, 0, 0, 0, 0};
const uint8_t CURRENT_PWM[] = {19, 2, 2, 2, 0, 0, 0, 0, 0, 0};
const uint8_t CURRENT_SPEED[] = {20, 3, 2, 2, 2, 0, 0, 0, 0, 0};
const uint8_t SONAR_DISTANCE[] = {23, 4, 1, 1, 1, 1, 0, 0, 0, 0};
const uint8_t ORDER_COMPLETE[] = {26, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t ROBOT_BLOCKED[] = {28, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t UPDATE_SCREEN[] = {30, 2, 2, 1, 0, 0, 0, 0, 0, 0};
const uint8_t FETCH_PUCK[] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t PUCK_FETCHED_CHIEF[] = {41, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t SET_DOCK_HEIGHT[] = {42, 2, 2, 2, 0, 0, 0, 0, 0, 0};
const uint8_t YOUR_DOCK_HAS_FULLFILLED_YOUR_REQUEST[] = {43, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t FRAMES[][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 2, 1, 1, 0, 0, 0, 0, 0, 0},
	{4, 3, 2, 2, 2, 0, 0, 0, 0, 0},
	{5, 2, 2, 2, 0, 0, 0, 0, 0, 0},
	{7, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{8, 4, 2, 2, 2, 1, 0, 0, 0, 0},
	{9, 3, 2, 2, 1, 0, 0, 0, 0, 0},
	{10, 1, 2, 0, 0, 0, 0, 0, 0, 0},
	{12, 3, 2, 2, 2, 0, 0, 0, 0, 0},
	{13, 3, 2, 2, 2, 0, 0, 0, 0, 0},
	{14, 3, 2, 2, 2, 0, 0, 0, 0, 0},
	{15, 2, 2, 2, 0, 0, 0, 0, 0, 0},
	{16, 3, 2, 2, 2, 0, 0, 0, 0, 0},
	{17, 3, 2, 2, 2, 0, 0, 0, 0, 0},
	{18, 3, 2, 2, 2, 0, 0, 0, 0, 0},
	{19, 2, 2, 2, 0, 0, 0, 0, 0, 0},
	{20, 3, 2, 2, 2, 0, 0, 0, 0, 0},
	{23, 4, 1, 1, 1, 1, 0, 0, 0, 0},
	{26, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{28, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{30, 2, 2, 1, 0, 0, 0, 0, 0, 0},
	{40, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{41, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{42, 2, 2, 2, 0, 0, 0, 0, 0, 0},
	{43, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
const int FRAMES_LENGTH = 25;
// END OF PROTOCOL
