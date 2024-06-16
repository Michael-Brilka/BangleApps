#pragma once
#include <vector>

class DataElements
{
public:



	struct HRM
	{
		int time = 0;
		int ppgVal = 0;
	};

	struct Barometer
	{
		int time = 0;
		double temperature = 0;
		double pressure = 0;
		double height = 0;
	};

	struct Accelerometer
	{
		int time = 0;
		double x = 0;
		double y = 0;
		double z = 0;
	};

	struct Magnetude
	{
		int time = 0;
		double magnitude = 0;
	};

	struct Compass
	{
		int time = 0;
		int x = 0;
		int y = 0;
		int z = 0;
		double heading;
	};

	struct GPS
	{
		int time = 0;
		double x = 0;
		double y = 0;
		double z = 0;
	};

private:

};
