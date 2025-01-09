//
// Created by apin on 09.01.2025.
//

#ifndef VINS_FOCUS_FEATUREDETECTOR_HPP
#define VINS_FOCUS_FEATUREDETECTOR_HPP


#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/tracking.hpp>


#include "core/map/KeyFrame.hpp"
#include "core/map/Map.hpp"


namespace vins {
namespace sensors {

class FeatureDetector {
public:
    /*********Public fields*********/


    /*********Public methods*********/

    FeatureDetector(const cv::FileStorage& config, std::shared_ptr<vins::core::Map> map);

    virtual ~FeatureDetector();

protected:
    /*********Protected fields*********/


    /*********Protected methods*********/


private:
    /*********Private fields*********/
    cv::FileStorage _config;

    std::shared_ptr<vins::core::Map> _map;

    cv::Ptr<cv::Feature2D> _detector{nullptr};

    /*********Private methods*********/
    void _instantiate_detector();


};

}; //namespace sensors
}; //namespace vins


#endif //VINS_FOCUS_FEATUREDETECTOR_HPP
