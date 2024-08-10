#include "DatasetHandler.hpp"
#include <fstream>
#include <dirent.h>
#include <algorithm>

// #include "../../vins_utils/print_info.hpp"

#include "vins_utils/print_info.hpp"

using namespace vins_core;
using namespace vins_utils;

DatasetHandler::DatasetHandler(std::string config_path)
{
    cv::FileStorage fs(config_path, cv::FileStorage::READ);

    if (!fs.isOpened()) {
        VINS_ERROR("Unable to open dataset config file: %s", config_path);
        return;
    }

    std::string dataset;
    std::string seq;
    fs["current"]["dataset"] >> dataset;
    fs["current"]["sequence"] >> seq;

    VINS_DEBUG("%s", dataset.c_str());

    std::string image_path = "datasets/" + dataset + "/sequences/" + seq + "/";
    std::string poses_path = "datasets/" + dataset + "/poses/" + seq + ".txt";
    std::string calib_path = "datasets/" + dataset + "/calibration/" + seq + ".yaml";
    std::string times_path = "datasets/" + dataset + "/times/" + seq + ".txt";

    _load_images(image_path);
    _load_times(times_path);
    _load_poses(poses_path);
    _load_calibration(calib_path);

    fs["datasets"][dataset]["fps"] >> fps;
    
    fs.release();
}


DataPackageBase DatasetHandler::read()
{
    static int counter = 0;
    DatasetPackage package = get_pack(counter);
    counter++;
    return package;
}


DatasetPackage DatasetHandler::get_pack(int index)
{
    cv::Mat R = (
        cv::Mat_<double>(3, 3) <<
        poses.at<double>(index, 0), poses.at<double>(index, 1), poses.at<double>(index, 2),
        poses.at<double>(index, 4), poses.at<double>(index, 5), poses.at<double>(index, 6),
        poses.at<double>(index, 8), poses.at<double>(index, 9), poses.at<double>(index, 10)
    );

    DatasetPackage package;

    package.timestamp = times.at(index);

    package.coordinates = cv::Vec<double, 3>(
        poses.at<double>(index, 3),
        poses.at<double>(index, 7),
        poses.at<double>(index, 11)
    );

    package.rotation = R;

    package.img = cv::imread(images.at(index));
    
    return package;
}

DatasetPackage DatasetHandler::operator[](int index)
{
    DatasetPackage pkg = get_pack(index);
    return pkg;
}


void DatasetHandler::print_info()
{
    std::cout << "Image number: " << images.size() << std::endl;
    std::cout << "Timings number: " << times.size() << std::endl;
    std::cout << "Ground-truth poses number: " << poses.size() << std::endl;
    std::cout << "Instric params" << std::endl << calibration << std::endl;

    return;
}





void DatasetHandler::_load_images(std::string path)
{
    DIR* dir = opendir(path.c_str());

    if (dir == nullptr) {
        std::cerr << "Unable to open directory " << path << std::endl;
        return;
    }

    struct dirent* entry;
    while( (entry = readdir(dir)) != nullptr ) {
        std::string filename = entry->d_name;
        if (filename != "." && filename != "..") {
            images.push_back(path + filename);
        }
    }

    closedir(dir);

    std::sort(images.begin(), images.end());

    return;
}


void DatasetHandler::_load_calibration(std::string path)
{
    cv::FileStorage calib_file(path, cv::FileStorage::READ);

    if (!calib_file.isOpened()) {
        std::cerr << "Unable to open file " << path << std::endl;
        return;
    }

    calib_file["instrict"] >> calibration;

    calib_file.release();
    return;
}


void DatasetHandler::_load_times(std::string path)
{
    std::ifstream times_file(path);

    if (!times_file.is_open()) {
        std::cerr << "Unable to open file " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(times_file, line)) {
        std::istringstream iss(line);
        float value;
        if (iss >> value) {
            times.push_back(value);
        } else {
            std::cerr << "Error while reading line " << line << std::endl; 
        }
    }

    times_file.close();
    return;
}


void DatasetHandler::_load_poses(std::string path)
{
    std::ifstream poses_file(path);

    if (!poses_file.is_open()) {
        std::cerr << "Unable to open file " << path << std::endl;
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