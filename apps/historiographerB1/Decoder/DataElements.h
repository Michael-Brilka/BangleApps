#pragma once
#include <vector>

class DataElements
{
public:

	struct GloveData
	{
		int64_t time = 0;
		int single0x = 0;
		int single0y = 0;
		int single0z = 0;
		int single1x = 0;
		int single1y = 0;
		int single1z = 0;
		int single2x = 0;
		int single2y = 0;
		int single2z = 0;
		int single3x = 0;
		int single3y = 0;
		int single3z = 0;
		int single4x = 0;
		int single4y = 0;
		int single4z = 0;
		int single5x = 0;
		int single5y = 0;
		int single5z = 0;
	};	

	struct HRM
	{
		int64_t time = 0;
		int ppgVal = 0;
	};

	struct Barometer
	{
		int64_t time = 0;
		double temperatureD = 0;
		double pressureD = 0;
		double heightD = 0;
		float temperatureF = 0;
		float pressureF = 0;
		float heightF = 0;
	};

	struct Accelerometer
	{
		int64_t time = 0;
		double x = 0;
		double y = 0;
		double z = 0;
	};

	struct Magnitude
	{
		int64_t time = 0;
		double magnitude = 0;
	};

	struct Compass
	{
		int64_t time = 0;
		int x = 0;
		int y = 0;
		int z = 0;
		double headingD;
		float headingF;
	};

	struct GPS
	{
		int64_t time = 0;
		double xD = 0;
		double yD = 0;
		double zD = 0;

		float xF = 0;
		float yF = 0;
		float zF = 0;

	};

private:

};
