//
// Created by apin on 02.01.2025.
//

#include "VideoNode.hpp"
#include "sensors/real_sensors/video/basic_source/VideoSourceFactory.hpp"


using namespace vins::nodes;


VideoNode::VideoNode(const std::string &name, std::string config_path): Node(name) {
    _video_source = vins::sensors::VideoSourceFactory::createVideoSource(std::move(config_path));
};


VideoNode::VideoNode(const std::string &name, const cv::FileStorage &config): Node(name) {
    _video_source = vins::sensors::VideoSourceFactory::createVideoSource(config);
};


void VideoNode::init() {
    _video_source->print_info();
}


void VideoNode::run() {
    while (_running) {
        _video_source->read();
        std::this_thread::sleep_for(std::chrono::milliseconds(_video_source->fps_to_ms()));
    }
}