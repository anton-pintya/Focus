//
// Created by apin on 14.01.2025.
//

#ifndef VINS_FOCUS_FEATURETRACKER_HPP
#define VINS_FOCUS_FEATURETRACKER_HPP


#include <opencv2/opencv.hpp>
#include <memory>

#include "core/map/Map.hpp"


namespace vins {
namespace sensors {

class FeatureTracker {
public:
    /*********Public fields*********/


    /*********Public methods*********/
    FeatureTracker();

    FeatureTracker(const cv::FileStorage& config);

    FeatureTracker(const cv::FileStorage& config, std::shared_ptr<vins::core::Map> map);

    virtual ~FeatureTracker();

    void add_map(std::shared_ptr<vins::core::Map> map);

    void add_config(const cv::FileStorage& config);

    void init();

    void init(const cv::Mat& image, const cv::Mat& mask=cv::Mat());

    void track();

    void track(cv::Mat current_image);

    void track(cv::Mat previous_image, cv::Mat current_image, vins::core::KeyFrame* previous, vins::core::KeyFrame* current);

protected:
    /*********Protected fields*********/


    /*********Protected methods*********/


private:
    /*********Private fields*********/
    cv::FileStorage _config;
    std::shared_ptr<vins::core::Map> _map;

    std::vector<cv::Point2f> _prev_points;
    std::vector<cv::Point2f> _curr_points;

    cv::Mat _prev_image;
    cv::Mat _curr_image;

    std::vector<uchar>  _status{0};
    std::vector<float>  _error{0};
    cv::Size            _win_size{21, 21};
    int                 _max_level{0};
    cv::TermCriteria    _term_criteria;

    /*********Private methods*********/
    void _clear_points(vins::core::KeyFrame* prev, vins::core::KeyFrame* curr);

};

}; //namespace sensors
}; //namespace vins


#endif //VINS_FOCUS_FEATURETRACKER_HPP
