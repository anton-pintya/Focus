//
// Created by apin on 09.01.2025.
//

#include "FeatureDetector.hpp"

#include <utility>

#include "utils/print_info.hpp"

using namespace vins::sensors;


FeatureDetector::FeatureDetector(const cv::FileStorage& config, std::shared_ptr<vins::core::Map> map) {
    _config = config;
    _map = std::move(map);

    _instantiate_detector();
}


FeatureDetector::~FeatureDetector() = default;


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