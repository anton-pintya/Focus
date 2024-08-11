#include "CameraHandler.hpp"
#include "vins_utils/print_info.hpp"

using namespace vins_core;
using namespace vins_utils;



CameraHandler::CameraHandler(std::string config_path)
{
    cv::FileStorage fs(config_path, cv::FileStorage::READ);

    if (!fs.isOpened()) {
        VINS_ERROR("Unable to open video file config: %s", config_path.c_str());
        return;
    }

    fs["current"]["device"] >> device_number;
    fs["current"]["fps"] >> fps;

    fs.release();

    // std::string calib_path = video_folder + "/calibration/" + video_file.substr(0, video_file.size() - 3) + "yaml";

    camera.open(device_number);

    // _load_calibration(calib_path);
}


DataPackageBase CameraHandler::read()
{
    CameraPackage package;

    camera >> package.img;

    package.timestamp = 123;

    return package;
}


void CameraHandler::print_info()
{
    VideoSource::print_info();

    VINS_INFO("Deivce name: /dev/video%i", device_number);
    VINS_INFO("Capture FPS: %i", fps);
}
