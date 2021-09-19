/**
 * @file ds3231_lib.h
 * @author Denys Khmil
 * @brief This file contents ds3231 class
 */
#ifndef DS3231_LIB_H_
#define DS3231_LIB_H_

#include "main.h"

/**
 * @brief ds3231 class
 */
class ds3231{
public:
	ds3231(I2C_HandleTypeDef _i2c, uint8_t _deviceAddr);
	ds3231(I2C_HandleTypeDef _i2c);
	void setTime(uint8_t _hours, uint8_t _minutes, uint8_t _seconds);
	void setDate(uint8_t _day, uint8_t _month, uint8_t _year);
	void getTime(uint8_t *_hours, uint8_t *_minutes, uint8_t *_seconds);
	void getDate(uint8_t *_day, uint8_t *_month, uint8_t *_year);
	void setWeekday(uint8_t _weekday);
	uint8_t getWeekday();
private:
	I2C_HandleTypeDef i2c;
	uint8_t deviceAddr;

	uint8_t convertSend(uint8_t input);
	uint8_t convertReceive(uint8_t input);
};


#endif /* DS3231_LIB_H_ */
