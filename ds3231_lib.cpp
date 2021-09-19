/**
 * @file ds3231_lib.cpp
 * @author Denys Khmil
 * @brief This file contents all the functions for the ds3231 library 
 */
#include "ds3231_lib.h"

/**
  * @brief Values addresses
  */
#define HOURS_ADDR 0x02
#define MINUTES_ADDR 0x01
#define SECONDS_ADDR 0x00

#define DATE_ADDR 0x04
#define MONTH_ADDR 0x05
#define YEAR_ADDR 0x06
#define WEEKDAY_ADDR 0x03


/**
 * @brief ds3231 constructor with specified i2c address and device adress
 * @param _i2c: ds3231 i2c port.
 * @param _address: address of a sensor.
 */
ds3231::ds3231(I2C_HandleTypeDef _i2c, uint8_t _deviceAddr){
	this->i2c = _i2c;
	this->deviceAddr = _deviceAddr;
}


/**
 * @brief ds3231 constructor with specified i2c address and default device adress
 * @param _i2c: ds3231 i2c port.
 */
ds3231::ds3231(I2C_HandleTypeDef _i2c){
	this->i2c = _i2c;
	this->deviceAddr = 0b1101000;
}


/**
 * @brief Set hours, minutes and seconds
 * @param _hours: hours value.
 * @param _minutes: minutes value.
 * @param _seconds: seconds value.
 */
void ds3231::setTime(uint8_t _hours, uint8_t _minutes, uint8_t _seconds){
	uint8_t buffer[2] = {HOURS_ADDR, 0};
	buffer[1] = this->convertSend(_hours);
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), buffer, 2, 100);

	buffer[0] = MINUTES_ADDR;
	buffer[1] = this->convertSend(_minutes);
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), buffer, 2, 100);

	buffer[0] = SECONDS_ADDR;
	buffer[1] = this->convertSend(_seconds);
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), buffer, 2, 100);
}


/**
 * @brief Set day, month and year
 * @param _day: day value.
 * @param _month: month value.
 * @param _year: year value.
 */
void ds3231::setDate(uint8_t _day, uint8_t _month, uint8_t _year){
	uint8_t buffer[2] = {DATE_ADDR, 0};
	buffer[1] = this->convertSend(_day);
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), buffer, 2, 100);

	buffer[0] = MONTH_ADDR;
	buffer[1] = this->convertSend(_month);
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), buffer, 2, 100);

	buffer[0] = YEAR_ADDR;
	buffer[1] = this->convertSend(_year);
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), buffer, 2, 100);
}


/**
 * @brief Get hours, minutes and seconds
 * @param _hours: pointer to hours variable .
 * @param _minutes: pointer to minutes variable .
 * @param _seconds: pointer to seconds variable .
 */
void ds3231::getTime(uint8_t *_hours, uint8_t *_minutes, uint8_t *_seconds){
	uint8_t buffer = HOURS_ADDR;
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	HAL_I2C_Master_Receive(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	*_hours = this->convertReceive(buffer);

	buffer = MINUTES_ADDR;
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	HAL_I2C_Master_Receive(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	*_minutes = this->convertReceive(buffer);;

	buffer = SECONDS_ADDR;
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	HAL_I2C_Master_Receive(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	*_seconds = this->convertReceive(buffer);
}


/**
 * @brief Get day, month and year.
 * @param _day: pointer to day variable .
 * @param _month: pointer to month variable .
 * @param _year: pointer to year variable .
 */
void ds3231::getDate(uint8_t *_day, uint8_t *_month, uint8_t *_year){
	uint8_t buffer = DATE_ADDR;
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	HAL_I2C_Master_Receive(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	*_day = this->convertReceive(buffer);

	buffer = MONTH_ADDR;
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	HAL_I2C_Master_Receive(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	*_month = this->convertReceive(buffer);;

	buffer = YEAR_ADDR;
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	HAL_I2C_Master_Receive(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	*_year = this->convertReceive(buffer);

}


/**
 * @brief Set weekday (1-7).
 * @param _weekday: Weekday value (1-7).
 */
void ds3231::setWeekday(uint8_t _weekday){
	uint8_t buffer[2] = {WEEKDAY_ADDR, 0};
	buffer[1] = this->convertSend(_weekday);
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), buffer, 2, 100);
}


/**
 * @brief Get weekday (1-7).
 * @retval Weekday (1-7).
 */
uint8_t ds3231::getWeekday(){
	uint8_t buffer = DATE_ADDR;
	HAL_I2C_Master_Transmit(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	HAL_I2C_Master_Receive(&this->i2c, (uint16_t)(this->deviceAddr << 1), &buffer, 1, 100);
	return	 this->convertReceive(buffer);
}


/**
 * @brief Prepare data to send (dec -> bin-dec).
 * @param input Data to convert
 * @retval Converted data (uint8_t).
 */
uint8_t ds3231::convertSend(uint8_t input){
return ((input/10)<<4)|(input%10);
}


/**
 * @brief Convert received data (bin-dec -> dec).
 * @param input Data to convert
 * @retval Converted data (uint8_t).
 */
uint8_t ds3231::convertReceive(uint8_t input){
return ((input>>4)*10+(0x0F&input));
}