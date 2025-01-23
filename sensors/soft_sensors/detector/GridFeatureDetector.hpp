//
// Created by apin on 22.01.2025.
//

#ifndef VINS_FOCUS_GRIDFEATUREDETECTOR_HPP
#define VINS_FOCUS_GRIDFEATUREDETECTOR_HPP


#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/tracking.hpp>

#include "FeatureDetector.hpp"


namespace vins {
namespace sensors {

class GridFeatureDetector {
public:
    /*********Public fields*********/


    /*********Public methods*********/
    GridFeatureDetector() = default;

    GridFeatureDetector(const cv::FileStorage& config);

    GridFeatureDetector(FeatureDetector* detector, int grid_rows, int grid_cols, int max_features);

    void add_detector(FeatureDetector* detector);

    void add_config(const cv::FileStorage& config);

    void set_grid(int grid_rows, int grid_cols);

    void set_max_features(int max_features);

    cv::Size get_grid_size();

    int get_max_features() const;

    void detect(cv::Mat image, std::vector<cv::KeyPoint>& keypoints, const cv::Mat& mask=cv::Mat());

protected:
    /*********Protected fields*********/


    /*********Protected methods*********/


private:
    /*********Private fields*********/
    cv::FileStorage _config;

    cv::Ptr<FeatureDetector> _base_detector{nullptr};

    int _grid_rows{0};
    int _grid_cols{0};
    int _max_features{0};

    /*********Private methods*********/


};

}; // namespace sensors
}; // namespace vins


#endif //VINS_FOCUS_GRIDFEATUREDETECTOR_HPP
