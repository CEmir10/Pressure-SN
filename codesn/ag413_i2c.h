#ifndef INC_AG413_I2C_H_
#define INC_AG413_I2C_H_

// Sensor code: AG413-001M-2-TP
// Supply Voltage: 3.3 VDC
// Pressure Value: 1 MPa




//Status codes
#define STATUS_NORMAL 				0x0
#define STATUS_CMD_MODE 			0x1
#define STATUS_STALE_DATA 			0x2
#define STATUS_EEPROM_ERR 			0X3

//Sensor I2C address
#define AG413_SENSOR_ADDR					0x28

//Pressure formula constants
#define PRESSURE_ERROR 				0xDD   // 221 dec is 0xDD in hex
#define PRESSURE_ALFA_UPPER_VALUE 	0x1CCD // 7373 dec is 0x1CCD in hex		
#define PRESSURE_ALFA_LOWER_VALUE	0x1F4  // 500 dec is 0x1F4 in hex
#define PRESSURE_BETA_VALUE			0x333

// According to datasheet, Master receives 4 words from Slave (sensor)
//here we store readings from sensor
typedef struct SensorReading
{
	char StatusData;	 //first 2 bits of the first word
	int PressureData; 	 //data from first two words
	int TemperaturaData; //data from other two words
} SensorData;


int calculateTemperature(SensorData sensor_data);
/*
double calculateTemperature(SensorData sensor_data) 
{
	int temperature = 0;
	temperature = ( ( 200/2047 )*sensor_data.TemperaturaData ) - 50;
	return temperature;
}
*/

double calculatePressure (SensorData sensor_data, int temperature);
/*
double calculatePressure (SensorData pressure_data, int temperature)
{
	double pressure - 0.0;
	int error_multiplier = getPressureErrorMultiplier(temperature);
	
	pressure = (sensor_data.PressureData - PRESSURE_BETA_VALUE + (PRESSURE_ERROR*error_multiplier ) ) / (PRESSURE_ALFA_UPPER_VALUE/PRESSURE_ALFA_LOWER_VALUE);]
	
	return pressure;
}
*/
//obtain error multiplier for pressure formula, graph from page 10 of datasheet is reference


int getPressureErrorMultiplier(int temperature);
/*
int getPressureErrorMultiplier(int temperature) 
{
	int error_multiplier = 0;
	
	if (temperature >= -40) && (temperature < -30) 
	{
		error_multiplier = 3;
	}
	else if (temperature >= -30) && (temperature < -10) 
	{
		error_multiplier = 2;
	}
	else if (temperature >= -10) && (temperature < 95) 
	{
		error_multiplier = 1;
	}
	else if (temperature >= -95) && (temperature < -115) 
	{
		error_multiplier = 2;
	}
	else 
	{
		error_multiplier = 3;
	}
	
}

static void write(struct device *dev, u8_t data)
{
	
	if (i2c_write(dev, data, 1,AG413_SENSOR_ADDR ) < 0) { //write a set amount of data to an I2C device
		LOG_ERR("Error writing register.");
	}
}


*/

#endif /* INC_AG431_I2C_H_ */