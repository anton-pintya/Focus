//
// Created by apin on 19.12.2024.
//

#include "vins_core/video_source/inc/StreamHandler.hpp"
#include "vins_utils/print_info.hpp"


using namespace vins_core;
using namespace vins_utils;


StreamHandler::StreamHandler(std::string config_path)
{
    cv::FileStorage fs(config_path, cv::FileStorage::READ);

    if (!fs.isOpened()) {
        VINS_ERROR("Unable to open video file config: %s", config_path.c_str());
        return;
    }

    fs["current"]["pipeline"] >> pipeline;

    video.open(pipeline, cv::CAP_GSTREAMER);
}


DataPackageBase StreamHandler::read()
{
    VideoPackage package;
    video >> package.img;
    package.timestamp = _get_time_since_first_call();

    return package;
}


void StreamHandler::print_info()
{
    VideoSource::print_info();

    VINS_INFO("Gstreamer pipeline: ", pipeline.c_str());
}