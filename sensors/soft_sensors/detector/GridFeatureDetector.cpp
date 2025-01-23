//
// Created by apin on 22.01.2025.
//

#include "GridFeatureDetector.hpp"


using namespace vins::sensors;


GridFeatureDetector::GridFeatureDetector(const cv::FileStorage& config):
    _config(config)
{
    // do something
}

GridFeatureDetector::GridFeatureDetector(FeatureDetector* detector, int grid_rows, int grid_cols, int max_features) :
    _base_detector(detector), _grid_rows(grid_rows), _grid_cols(grid_cols), _max_features(max_features)
{
    // do something
}

void GridFeatureDetector::add_detector(FeatureDetector* detector) {
    _base_detector = detector;
}

void GridFeatureDetector::add_config(const cv::FileStorage& config) {
    _config = config;
    _base_detector->add_config(config);
}


void GridFeatureDetector::set_grid(int grid_rows, int grid_cols) {
    _grid_rows = grid_rows;
    _grid_cols = grid_cols;
}


void GridFeatureDetector::set_max_features(int max_features) {
    _max_features = max_features;
}


cv::Size GridFeatureDetector::get_grid_size() {
    return {_grid_cols, _grid_rows};
}

int GridFeatureDetector::get_max_features() const {
    return _max_features;
}


void GridFeatureDetector::detect(cv::Mat image, std::vector<cv::KeyPoint>& keypoints, const cv::Mat& mask) {
    // do something
//    keypoints.clear();

    // Split the image into a grid
    int cell_width = image.cols / _grid_cols;
    int cell_height = image.rows / _grid_rows;

    for (int i = 0; i < _grid_rows; i++) {
        for (int j = 0; j < _grid_cols; j++) {
            // Select cell as a region of interest
            cv::Rect roi(j * cell_width, i * cell_height, cell_width, cell_height);
            cv::Mat cell = image(roi);

            // Use vins::sensors::FeatureDetector to detect keypoints in the cell
            std::vector<cv::KeyPoint> cell_keypoints;
            _base_detector->detect(cell, cell_keypoints);

            // Apply keypoints filter to retain only the best keypoints by response
            cv::KeyPointsFilter::removeDuplicated(cell_keypoints);
            cv::KeyPointsFilter::retainBest(cell_keypoints, _max_features);

            // Fulfill vector of keypoints with cell-to-image coordinates transformation
            for (auto& kp : cell_keypoints) {
                kp.pt.x += j * cell_width;
                kp.pt.y += i * cell_height;
                keypoints.push_back(kp);
            }
        }
    }
}