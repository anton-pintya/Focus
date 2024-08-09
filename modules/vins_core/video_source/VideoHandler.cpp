#include "VideoHandler.hpp"
#include "vins_utils/print_info.hpp"


using namespace vins_core;
using namespace vins_utils;

VideoHandler::VideoHandler(const std::string config_path)
{
    cv::FileStorage fs(config_path, cv::FileStorage::READ);

    if (!fs.isOpened()) {
        VINS_ERROR("Unable to open video file config: %s", config_path);
        return;
    }

    fs["current"]["path"] >> video_folder;
    fs["current"]["video"] >> video_file;
    std::string path_to_video = video_folder + "/sequences/" + video_file;

    printf("%s\n", path_to_video.c_str());

    
}