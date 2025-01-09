//
// Created by apin on 09.01.2025.
//

#ifndef VINS_FOCUS_KEYFRAME_HPP
#define VINS_FOCUS_KEYFRAME_HPP


#include <opencv2/opencv.hpp>
#include "core/map/Landmark.hpp"

namespace vins {
namespace core {

class KeyFrame {
public:
    /*********Public fields*********/
    uint64_t id;
    cv::Mat4d pose;
    std::vector<cv::KeyPoint> keypoints;
//    std::vector<vins::core::Landmark*> observed_landmarks;

    std::vector<uint64_t> observed_landmarks;

    cv::Mat image;

    /*********Public methods*********/


protected:
    /*********Protected fields*********/


    /*********Protected methods*********/


private:
    /*********Private fields*********/
    cv::Mat4d _imu_pose;
    cv::Mat4d _camera_pose;

    /*********Private methods*********/


};

}; //namespace core
}; //namespace vins



#endif //VINS_FOCUS_KEYFRAME_HPP
