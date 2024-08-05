#include "DatasetHandler.hpp"
#include <fstream>
#include <dirent.h>
#include <algorithm>

// #include "../../vins_utils/print_info.hpp"

using namespace vins_core;


DatasetHandler::DatasetHandler(std::string config_path)
{
    cv::FileStorage fs(config_path, cv::FileStorage::READ);

    if (!fs.isOpened()) {
        std::cerr << "Unable to open file " << config_path << std::endl;
        return;
    }

    fs["current"]["source"] >> data_source;

    if (data_source == "dataset") 
    {
        std::string dataset;
        std::string seq;
        fs["current"]["dataset"] >> dataset;
        fs["current"]["sequence"] >> seq;

        std::string image_path = "./datasets/" + dataset + "/sequences/" + seq + "/";
        std::string poses_path = "./datasets/" + dataset + "/poses/" + seq + ".txt";
        std::string calib_path = "./datasets/" + dataset + "/calibration/" + seq + ".yaml";
        std::string times_path = "./datasets/" + dataset + "/times/" + seq + ".txt";

        _load_images(image_path);
        _load_times(times_path);
        _load_poses(poses_path);
        _load_calibration(calib_path);

        fs["datasets"][dataset]["fps"] >> fps;
    } 
    else if (data_source == "video") 
    {

    } 
    else if (data_source == "camera")
    {

    }
    
    fs.release();
}


DataPackage DatasetHandler::get_pack(int index)
{
    cv::Mat R = (
        cv::Mat_<double>(3, 3) <<
        poses.at<double>(index, 0), poses.at<double>(index, 1), poses.at<double>(index, 2),
        poses.at<double>(index, 4), poses.at<double>(index, 5), poses.at<double>(index, 6),
        poses.at<double>(index, 8), poses.at<double>(index, 9), poses.at<double>(index, 10)
    );

    DataPackage package = {
        .timestamp = times.at(index),
        .coordinates = cv::Vec<double, 3>(
            poses.at<double>(index, 3),
            poses.at<double>(index, 7),
            poses.at<double>(index, 11)
        ),
        .rotation = R,
        .img = cv::imread(images.at(index))
    };
    
    return package;
}

DataPackage DatasetHandler::operator[](int index)
{
    DataPackage pkg = get_pack(index);
    return pkg;
}


void DatasetHandler::print_info()
{
    if (data_source == "dataset") {

        std::cout << "DATASET" << std::endl;
        std::cout << "Image number: " << images.size() << std::endl;
        std::cout << "Timings number: " << times.size() << std::endl;
        std::cout << "Ground-truth poses number: " << poses.size() << std::endl;
        std::cout << "Instric params" << std::endl << calibration << std::endl;

    } else if (data_source == "video") {

        std::cout << "video" << std::endl;

    } else if (data_source == "camera") {

        std::cout << "camera" << std::endl;

    }

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