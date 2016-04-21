/*
 * Crossroad.h
 *
 *  Created on: 16/04/2016
 *      Author: Inês
 */

#ifndef SRC_CROSSROAD_H_
#define SRC_CROSSROAD_H_

#include <math.h>

class Crossroad{
	unsigned int id;
	float latitude_in_degrees;
	float longitude_in_degrees;
	float longitude_in_radians;
	float latitude_in_radians;
public:
	Crossroad(unsigned int id, float lat_d, float lon_d, float lon_r, float lat_r): id(id), latitude_in_degrees(lat_d),
				longitude_in_degrees(lon_d), longitude_in_radians(lon_r), latitude_in_radians(lat_r){}

	float getLatitudeInDegrees() const {
		return latitude_in_degrees;
	}

	float getLatitudeInRadians() const {
		return latitude_in_radians;
	}

	float getLongitudeInDegrees() const {
		return longitude_in_degrees;
	}

	float getLongitudeInRadians() const {
		return longitude_in_radians;
	}

	bool operator == (const Crossroad &c2) const{

		return id == c2.id;
	}

	int getDist(Crossroad c2){
		int R = 6371000; // metres
		float lat1 = latitude_in_radians;
		float lat2 = c2.latitude_in_radians;
		float deltaLat = lat2 - lat1;
		float deltaLon = c2.longitude_in_radians - longitude_in_radians;

		float a = sin(deltaLat/2) * sin(deltaLat/2) +
		        cos(lat1) * cos(lat2) *
		        sin(deltaLon/2) * sin(deltaLon/2);
		float c = 2 * atan2(sqrt(a), sqrt(1-a));

		return R * c;
	}
};


#endif /* SRC_CROSSROAD_H_ */
