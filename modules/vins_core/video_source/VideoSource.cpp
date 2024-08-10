#include <fstream>
#include <dirent.h>

#include "VideoSource.hpp"

#include "vins_utils/print_info.hpp"


using namespace vins_core;
using namespace vins_utils;

void VideoSource::print_info()
{
    VINS_INFO("VIDEO SOURCE INFO");

    if (has_ground_truth()) {
        std::cout << "Ground-truth poses number: " << poses.size() << std::endl;
    } else {
        VINS_ERROR("No available ground-truth data for given source or file");
    }

    if (!calibration.empty()) {
        std::cout << "Instric params:" << std::endl << calibration << std::endl;
    } else {
        VINS_ERROR("No available calibration data");
    }
}


void VideoSource::_load_calibration(std::string path)
{
    cv::FileStorage calib_file(path, cv::FileStorage::READ);

    if (!calib_file.isOpened()) {
        VINS_ERROR("Unable to open file %s", path.c_str());
        return;
    }

    calib_file["instrict"] >> calibration;

    calib_file.release();
    return;
}


void VideoSource::_load_poses(std::string path)
{
    std::ifstream poses_file(path);

    if (!poses_file.is_open()) {
        VINS_ERROR("Unable to open file %s", path.c_str());
        return;
    }

    has_gt = true;

    int lines = std::count(
        std::istreambuf_iterator<char>(poses_file), 
        std::istreambuf_iterator<char>(), '\n'
    );

    poses_file.close();
    poses_file.open(path);

    poses = cv::Mat::zeros(lines, 12, CV_64F);

    std::string line;

    for (int i = 0; i < lines; i++) {
        std::getline(poses_file, line);
        std::istringstream iss(line);

        double value;
        
        for (int j = 0; j < 12; j++)
        {
            iss >> value;
            poses.at<double>(i, j) = value;
        }
    }

    poses_file.close();
    return;
}