//
// Created by apin on 19.12.2024.
//

#include "sensors/video/video.hpp"
#include "utils/print_info.hpp"


using namespace vins::sensors;

using namespace vins_utils;


StreamHandler::StreamHandler(cv::FileNode config)
{
    config["pipeline"] >> pipeline;

    video.open(pipeline, cv::CAP_GSTREAMER);
}


DataPackageBase StreamHandler::read()
{
    VideoPackage package;
    video >> package.img;
    package.timestamp = _get_time_since_first_call();

    publish(package);

    return package;
}


void StreamHandler::print_info()
{
    VideoSource::print_info();

    VINS_INFO("Gstreamer pipeline: ", pipeline.c_str());
}