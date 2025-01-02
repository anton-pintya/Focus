//
// Created by apin on 02.01.2025.
//

#include "VideoNode.hpp"
#include "sensors/video/basic_source/VideoSourceFactory.hpp"


using namespace vins::nodes;


VideoNode::VideoNode(const std::string &name, std::string config_path): Node(name) {
    _imu_source = vins::sensors::VideoSourceFactory::createVideoSource(std::move(config_path));
};


void VideoNode::init() {
    _imu_source->print_info();
}


void VideoNode::run() {
    while (_running) {
        _imu_source->read();
        publish();
    }
}