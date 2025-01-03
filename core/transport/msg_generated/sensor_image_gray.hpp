#ifndef VINS_FOCUS_SENSOR_IMAGE_GRAY_HPP
#define VINS_FOCUS_SENSOR_IMAGE_GRAY_HPP


#include "../Topic.hpp"


#pragma pack(push, 1)
struct sensor_image_gray {
    uint64_t timestamp{0};
     uint16_t width;
     uint16_t height;
     uint8_t data[1920 * 1080];
    
};
#pragma pack(pop)

REGISTER_TOPIC(sensor_image_gray)

#endif //VINS_FOCUS_SENSOR_IMAGE_GRAY_HPP