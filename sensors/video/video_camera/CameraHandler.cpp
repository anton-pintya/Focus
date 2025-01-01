#include "sensors/video/video.hpp"
#include "utils/print_info.hpp"

using namespace vins::sensors;
using namespace vins_utils;



CameraHandler::CameraHandler(cv::FileNode config)
{
    config["device"] >> device_number;
    config["fps"] >> fps;

    camera.open(device_number);
}


DataPackageBase CameraHandler::read()
{
    CameraPackage package;
    camera >> package.img;
    package.timestamp = _get_time_since_first_call();

    publish(package);

    return package;
}


void CameraHandler::print_info()
{
    VideoSource::print_info();

    VINS_INFO("Deivce name: /dev/video%i", device_number);
    VINS_INFO("Capture FPS: %i", fps);
}
