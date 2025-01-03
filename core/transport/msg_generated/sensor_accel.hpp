#ifndef VINS_FOCUS_SENSOR_ACCEL_HPP
#define VINS_FOCUS_SENSOR_ACCEL_HPP


#include "../Topic.hpp"


#pragma pack(push, 1)
struct sensor_accel {
    uint64_t timestamp{0};
     float x;
     float y;
     float z;
    
};
#pragma pack(pop)

REGISTER_TOPIC(sensor_accel)

#endif //VINS_FOCUS_SENSOR_ACCEL_HPP