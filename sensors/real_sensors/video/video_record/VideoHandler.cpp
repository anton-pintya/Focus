#include "sensors/real_sensors/video/video.hpp"
#include "utils/print_info.hpp"


using namespace vins::sensors;

using namespace vins_utils;

VideoHandler::VideoHandler(cv::FileNode config)
{
    config["path"] >> video_folder;
    config["video"] >> video_file;
    config["fps"] >> fps;

//    std::string video_path = video_folder + "/sequences/" + video_file;
    std::string video_path = video_folder + "/" + video_file;
    std::string calib_path = video_folder + "/calibration/" + video_file.substr(0, video_file.size() - 3) + "yaml";
    std::string poses_path = video_folder + "/poses/" + video_file.substr(0, video_file.size() - 3) + "txt";

    bool res = video.open(video_path);

    if (!res) {
        VINS_ERROR("Failed to open video file %s", video_path.c_str());
        std::exit(EXIT_FAILURE);
    }

    _load_calibration(calib_path);
    _load_poses(poses_path);
}


void VideoHandler::read() {
    cv::Mat image;
    video >> image;
    publish(image);
}


void VideoHandler::print_info()
{
    VideoSource::print_info();

    VINS_INFO("Video folder: %s", video_folder.c_str());
    VINS_INFO("Video file: %s", video_file.c_str());
}