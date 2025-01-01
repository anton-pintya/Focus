#include "sensors/video/video.hpp"
#include "utils/print_info.hpp"


using namespace vins::sensors;

using namespace vins_utils;

VideoHandler::VideoHandler(cv::FileNode config)
{
    config["path"] >> video_folder;
    config["video"] >> video_file;
    config["fps"] >> fps;

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

    publish(package);

    return package;
}


void VideoHandler::print_info()
{
    VideoSource::print_info();

    VINS_INFO("Video folder: %s", video_folder.c_str());
    VINS_INFO("Video file: %s", video_file.c_str());
}