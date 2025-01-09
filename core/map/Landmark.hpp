//
// Created by apin on 09.01.2025.
//

#ifndef VINS_FOCUS_LANDMARK_HPP
#define VINS_FOCUS_LANDMARK_HPP


#include <opencv2/opencv.hpp>

#include "core/map/KeyFrame.hpp"


namespace vins {
namespace core {

class Landmark {
public:
    /*********Public fields*********/
    uint64_t id;
    cv::Point3d position;
//    std::vector<vins::core::KeyFrame*> observed_in_keyframe;

    std::vector<uint64_t> observed_in_keyframe;

    /*********Public methods*********/


protected:
    /*********Protected fields*********/


    /*********Protected methods*********/


private:
    /*********Private fields*********/


    /*********Private methods*********/

};

}; //namespace core
}; //namespace vins


#endif //VINS_FOCUS_LANDMARK_HPP
