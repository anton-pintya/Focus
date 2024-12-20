#include "vins_core/video_source/inc/VideoHandler.hpp"
#include "vins_utils/print_info.hpp"


using namespace vins_core;
using namespace vins_utils;

VideoHandler::VideoHandler(const std::string config_path)
{
    cv::FileStorage fs(config_path, cv::FileStorage::READ);

    if (!fs.isOpened()) {
        VINS_ERROR("Unable to open video file config: %s", config_path.c_str());
        return;
    }

    fs["current"]["path"] >> video_folder;
    fs["current"]["video"] >> video_file;
    fs["current"]["fps"] >> fps;

    fs.release();

    std::string video_path = video_folder + "/sequences/" + video_file;
    std::string calib_path = video_folder + "/calibration/" + video_file.substr(0, video_file.size() - 3) + "yaml";
    std::string poses_path = video_folder + "/poses/" + video_file.substr(0, video_file.size() - 3) + "txt";

    video.open(video_path);

    _load_calibration(calib_path);
    _load_poses(poses_path);
}


DataPackageBase VideoHandler::read()
{
    VideoPackage package;
    video >> package.img;
    package.timestamp = _get_time_since_first_call();

    return package;
}


void VideoHandler::print_info()
{
    VideoSource::print_info();

    VINS_INFO("Video folder: %s", video_folder.c_str());
    VINS_INFO("Video file: %s", video_file.c_str());
}