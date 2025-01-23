//
// Created by apin on 14.01.2025.
//

#include "FeatureTracker.hpp"

#include <utility>


using namespace vins::sensors;


FeatureTracker::FeatureTracker() = default;


FeatureTracker::FeatureTracker(const cv::FileStorage &config):
    _config(config)
{
    //
}


FeatureTracker::FeatureTracker(const cv::FileStorage &config, std::shared_ptr<vins::core::Map> map):
    _map(std::move(map)), _config(config)
{
    //
}


FeatureTracker::~FeatureTracker() = default;


void FeatureTracker::add_map(std::shared_ptr<vins::core::Map> map) {
    _map = std::move(map);
}


void FeatureTracker::add_config(const cv::FileStorage &config) {
    _config = config;
}


void FeatureTracker::init() {
    _config["win_size"] >> _win_size;

    _term_criteria = cv::TermCriteria(
            _config["criteria"]["type"],
            _config["criteria"]["max_count"],
            _config["criteria"]["epsilon"]
    );

    _max_level = _config["max_level"];
}


void FeatureTracker::init(const cv::Mat &image, const cv::Mat &mask) {
    _prev_image = image;
    init();
}


void FeatureTracker::track(cv::Mat previous_image, cv::Mat current_image, vins::core::KeyFrame* previous, vins::core::KeyFrame* current) {
    cv::KeyPoint::convert(previous->keypoints, _prev_points);
    cv::KeyPoint::convert(current->keypoints, _curr_points);

    cv::calcOpticalFlowPyrLK(
            previous_image, current_image,
            _prev_points, _curr_points,
            _status, _error,
            _win_size, _max_level, _term_criteria
    );

    cv::KeyPoint::convert(_curr_points, current->keypoints);

    _prev_image = previous_image;
    _curr_image = current_image;

    _clear_points(previous, current);
}


void FeatureTracker::track(cv::Mat current_image) {

    _status.clear();

    vins::core::KeyFrame* current_keyframe = &*_map->get_latest_keyframe();
    vins::core::KeyFrame* previous_keyframe = &*current_keyframe->get_previous();

    cv::KeyPoint::convert(previous_keyframe->keypoints, _prev_points);
    cv::KeyPoint::convert(current_keyframe->keypoints, _curr_points);

    cv::calcOpticalFlowPyrLK(
            _prev_image, current_image,
            _prev_points, _curr_points,
            _status, _error,
            _win_size, _max_level, _term_criteria
        );

    cv::KeyPoint::convert(_curr_points, current_keyframe->keypoints);

    _clear_points(&*current_keyframe, &*previous_keyframe);

    _prev_image = current_image;
}


void FeatureTracker::_clear_points(vins::core::KeyFrame *prev, vins::core::KeyFrame *curr) {

    int j = 0;
    for (int i = 0; i < _status.size(); i++) {

        cv::Point2f prev_point = prev->keypoints.at(i).pt;
        cv::Point2f curr_point = curr->keypoints.at(i).pt;

        bool pos_condition =
                (prev_point.x <= 0) || (prev_point.y <= 0) ||
                (curr_point.x <= 0) || (curr_point.y <= 0) ||
                (curr_point.x >= _curr_image.size().width) || (curr_point.y >= _curr_image.size().height) ||
                (prev_point.x >= _prev_image.size().width) || (prev_point.y >= _prev_image.size().height);


        cv::Vec2f flow = cv::Vec2f(curr_point - prev_point);
        bool len_condition = cv::norm(flow) >= 0.25 * cv::min(_curr_image.cols, _curr_image.rows);

        if (!_status.at(i) || pos_condition || len_condition) {
//        if (!_status.at(i) || pos_condition) {
            prev->keypoints.erase(prev->keypoints.begin() + (i - j));
            curr->keypoints.erase(curr->keypoints.begin() + (i - j));
            _status.erase(_status.begin() + (i - j));
            _error.erase(_error.begin() + (i - j));
            j++;
        }
    }
}