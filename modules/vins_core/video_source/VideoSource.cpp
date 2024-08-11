#include <fstream>
#include <dirent.h>
#include <chrono>

#include "VideoSource.hpp"

#include "vins_utils/print_info.hpp"


using namespace vins_core;
using namespace vins_utils;

void VideoSource::print_info()
{
    VINS_INFO("VIDEO SOURCE INFO");

    if (has_ground_truth()) {
        // std::cout << "Ground-truth poses number: " << poses.size() << std::endl;
        VINS_INFO("Number of poses: [%i x %i]", poses.size().width, poses.size().height);
    } else {
        VINS_ERROR("No available ground-truth data for given source or file");
    }

    if (!calibration.empty()) {
        VINS_INFO("Instric params:");
        std::cout << calibration << std::endl;
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



double VideoSource::_get_time_since_last_call()
{
    static auto last_call_time = std::chrono::steady_clock::now();

    auto current_time = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_time = current_time - last_call_time;

    last_call_time = current_time;

    return elapsed_time.count();
}


double VideoSource::_get_time_since_first_call()
{
    static double time_passed = 0;
    time_passed += _get_time_since_last_call();
    return time_passed;
}