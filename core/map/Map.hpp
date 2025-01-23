//
// Created by apin on 09.01.2025.
//

#ifndef VINS_FOCUS_MAP_HPP
#define VINS_FOCUS_MAP_HPP


#include "core/map/KeyFrame.hpp"
#include "core/map/Landmark.hpp"

#include <unordered_map>
#include <shared_mutex>
//#include <mutex>
#include <thread>

#include <opencv2/opencv.hpp>


namespace vins {
namespace core {

class Map {
public:
    /*********Public fields*********/
    std::unordered_map<uint64_t, KeyFrame*> keyframes;
    std::unordered_map<uint64_t, Landmark*> landmarks;

    /*********Public methods*********/
    Map() = default;

    void add_keyframe(KeyFrame* keyframe);

    void add_landmark(Landmark* landmark);

    void remove_keyframe(uint64_t keyframe_id);

    void remove_landmark(uint64_t landmark_id);

    KeyFrame* get_keyframe(uint64_t keyframe_id);

    Landmark* get_landmark(uint64_t landmark_id);

    KeyFrame* get_latest_keyframe();

    Landmark* get_latest_landmark();

    KeyFrame* wait_untill_update();


protected:
    /*********Protected fields*********/


    /*********Protected methods*********/


private:
    /*********Private fields*********/
//    mutable std::shared_mutex _mutex;
    std::mutex _read_mutex;
    std::mutex _write_mutex;

    uint64_t _latest_keyframe_id{UINT64_MAX};
    uint64_t _latest_landmark_id{UINT64_MAX};

    bool _new_added = false;

    /*********Private methods*********/


};

}; //namespace core
}; //namespace vins


#endif //VINS_FOCUS_MAP_HPP
