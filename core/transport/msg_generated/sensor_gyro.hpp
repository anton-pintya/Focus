#ifndef VINS_FOCUS_SENSOR_GYRO_HPP
#define VINS_FOCUS_SENSOR_GYRO_HPP


#include "../Topic.hpp"


#pragma pack(push, 1)
struct sensor_gyro {
    uint64_t timestamp{0};
     float x;
     float y;
     float z;
    
};
#pragma pack(pop)

REGISTER_TOPIC(sensor_gyro)

#endif //VINS_FOCUS_SENSOR_GYRO_HPP