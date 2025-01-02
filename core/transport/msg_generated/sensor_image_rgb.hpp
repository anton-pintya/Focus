#ifndef VINS_FOCUS_SENSOR_IMAGE_RGB_HPP
#define VINS_FOCUS_SENSOR_IMAGE_RGB_HPP


#include "../Topic.hpp"


#pragma pack(push, 1)
struct sensor_image_rgb {
     uint16_t width;
     uint16_t height;
     uint8_t r[1920 * 1080];
     uint8_t g[1920 * 1080];
     uint8_t b[1920 * 1080];
    
};
#pragma pack(pop)

REGISTER_TOPIC(sensor_image_rgb)

#endif //VINS_FOCUS_SENSOR_IMAGE_RGB_HPP