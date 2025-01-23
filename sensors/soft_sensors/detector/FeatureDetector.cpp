//
// Created by apin on 09.01.2025.
//

#include "FeatureDetector.hpp"

#include <utility>

#include "utils/print_info.hpp"

using namespace vins::sensors;


FeatureDetector::FeatureDetector() = default;


FeatureDetector::FeatureDetector(const cv::FileStorage& config):
    _config(config)
{
    _instantiate_detector();
}


FeatureDetector::FeatureDetector(const cv::FileStorage &config, std::shared_ptr<vins::core::Map> map):
    _config(config), _map(map)
{
    _instantiate_detector();
}


FeatureDetector::~FeatureDetector() = default;


void FeatureDetector::add_map(std::shared_ptr<vins::core::Map> map) {
    _map = std::move(map);
}


void FeatureDetector::add_config(const cv::FileStorage &config) {
    _config = config;
    _instantiate_detector();
}


void FeatureDetector::detect(cv::Mat image, const cv::Mat& mask) {

    vins::core::KeyFrame* keyframe = new vins::core::KeyFrame(_map->get_latest_keyframe());
    _detector->detect(image, keyframe->keypoints);

    if (keyframe->keypoints.size() == 0) {
        return;
    }

    _map->add_keyframe(keyframe);
}


void FeatureDetector::detect(cv::Mat image, std::vector<cv::KeyPoint>& keypoints) {
    _detector->detect(image, keypoints);
}


void FeatureDetector::detect(vins::core::KeyFrame* keyframe, cv::Mat image, const cv::Mat& mask) {
    _detector->detect(image, keyframe->keypoints);
}


void FeatureDetector::_instantiate_detector() {
    std::string detector_type = _config["general"]["detector_type"];

    if (detector_type == "ORB") {
        _detector = cv::ORB::create();
    } else if (detector_type == "FAST") {
        _detector = cv::FastFeatureDetector::create(_config[detector_type]);
    } else if (detector_type == "AKAZE") {
        _detector = cv::AKAZE::create();
    } else if (detector_type == "BRISK") {
        _detector = cv::BRISK::create(_config[detector_type]);
    } else if (detector_type == "KAZE") {
        _detector = cv::KAZE::create();
    } else if (detector_type == "SIFT") {
        _detector = cv::SIFT::create();
    } else {
        throw std::runtime_error("Unknown detector type: " + detector_type);
    }

    if (!_config[detector_type].empty()) {
        _detector->read(_config[detector_type]);
        vins_utils::VINS_INFO("Configs loaded for detector %s", detector_type.c_str());
    } else {
        throw std::runtime_error("Detector config is empty for detector type: " + detector_type);
    }
}