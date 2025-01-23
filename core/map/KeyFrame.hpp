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
    uint64_t counter = 0;

public:
    /*********Public fields*********/
    uint64_t id{0};
    cv::Mat4d pose;
    std::vector<cv::KeyPoint> keypoints;
    std::vector<uint64_t> observed_landmarks;


    /*********Public methods*********/
    KeyFrame(KeyFrame* previous) : _previous(previous) { id = count(); }

    KeyFrame* get_previous() { return _previous; }

    ~KeyFrame() { --count(); }


protected:
    /*********Protected fields*********/


    /*********Protected methods*********/


private:
    /*********Private fields*********/
    cv::Mat4d _imu_pose;
    cv::Mat4d _camera_pose;

    KeyFrame* _previous{nullptr};

    /*********Private methods*********/
    static uint64_t& count() { static uint64_t counter = 0; counter++; return counter; }

};

}; //namespace core
}; //namespace vins



#endif //VINS_FOCUS_KEYFRAME_HPP
