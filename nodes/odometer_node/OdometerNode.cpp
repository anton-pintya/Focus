//
// Created by apin on 10.01.2025.
//

#include "OdometerNode.hpp"
#include "utils/print_info.hpp"
#include "core/visualizer/Visualizer.hpp"

using namespace vins::nodes;


OdometerNode::OdometerNode(const std::string &name, const cv::FileStorage &config):
    Node(name), _config(config)
{
    _image_sub.subscribe();
}


OdometerNode::OdometerNode(const std::string &name, const cv::FileStorage &config, std::shared_ptr<vins::core::Map> map):
    Node(name), _map(map), _config(config)
{
    _image_sub.subscribe();

    _detector.add_map(map);
    _tracker.add_map(map);
}


void OdometerNode::configurate_detector(const cv::FileStorage &config) {
    _detector.add_config(config);
    _grid_detector.add_detector(&_detector);
    _grid_detector.add_config(config);
}


void OdometerNode::configurate_tracker(const cv::FileStorage &config) {
    _tracker.add_config(config);
}


void OdometerNode::init() {
    _grid_detector.set_grid(5, 5);
    _grid_detector.set_max_features(30);

    static sensor_image init_msg = _image_sub.receive();

    if (init_msg.timestamp == 0) {
        vins_utils::VINS_DEBUG("No frame was posted, initialization will be delayed");
        return;
    } else {
        int image_type = init_msg.channels == 3 ? CV_8UC3 : CV_8UC1;

        cv::Mat image;
        switch (image_type) {
            case CV_8UC1:
                image = cv::Mat(init_msg.height, init_msg.width, image_type, init_msg.r);
                break;
            case CV_8UC3:
                std::vector<cv::Mat> bgr(3);
                bgr[0] = cv::Mat(init_msg.height, init_msg.width, CV_8UC1, init_msg.r);
                bgr[1] = cv::Mat(init_msg.height, init_msg.width, CV_8UC1, init_msg.g);
                bgr[2] = cv::Mat(init_msg.height, init_msg.width, CV_8UC1, init_msg.b);
                cv::merge(bgr, image);
                break;
        }

        _tracker.init(image);
        _last_image = image;

        // Ensure map has no KeyFrame
        if (_map->get_latest_keyframe() == nullptr) {
            vins_utils::VINS_DEBUG("Need to add first keyframe in map");

            vins::core::KeyFrame* first_keyframe = new vins::core::KeyFrame(nullptr);
//            _detector.detect(first_keyframe, image);
            _grid_detector.detect(image, first_keyframe->keypoints);

            if (first_keyframe->keypoints.empty()) {
                vins_utils::VINS_DEBUG("No keypoints found, initialization will be delayed");
                return;
            }

            _first_points_found = first_keyframe->keypoints.size();

            _map->add_keyframe(first_keyframe);
        } else {
            vins_utils::VINS_DEBUG("Map already has keyframe");
        }
    }
}


void OdometerNode::add_map(std::shared_ptr<vins::core::Map> map) {
    _map = std::move(map);
    _detector.add_map(map);
    _tracker.add_map(map);
}


cv::Mat OdometerNode::get_last_image() {
    return _last_image;
}


void OdometerNode::run() {
    static uint x_step = 0;
    static uint y_step = 0;

    while (_running) {
        sensor_image msg = _image_sub.receive();
        int image_type = msg.channels == 3 ? CV_8UC3 : CV_8UC1;

        cv::Mat image;
        switch (image_type) {
            case CV_8UC1:
                image = cv::Mat(msg.height, msg.width, image_type, msg.r);
                break;
            case CV_8UC3:
                std::vector<cv::Mat> bgr(3);
                bgr[0] = cv::Mat(msg.height, msg.width, CV_8UC1, msg.r);
                bgr[1] = cv::Mat(msg.height, msg.width, CV_8UC1, msg.g);
                bgr[2] = cv::Mat(msg.height, msg.width, CV_8UC1, msg.b);
                cv::merge(bgr, image);
                break;
        }

        if (image.empty()) {
            continue;
        }

        vins::core::KeyFrame* previous = &*_map->get_latest_keyframe();

        if (previous == nullptr) {
            init();
            continue;
        }

        vins::core::KeyFrame* current = new vins::core::KeyFrame(previous);

        if (previous->keypoints.size() < 0.4 * _first_points_found) {
//            _detector.detect(previous, _last_image);
            _grid_detector.detect(_last_image, previous->keypoints);

            _first_points_found = previous->keypoints.size();
            _last_image = image;
        }

        _tracker.track(_last_image, image, previous, current);

        _map->add_keyframe(current);

        _last_image = image;
    }
}