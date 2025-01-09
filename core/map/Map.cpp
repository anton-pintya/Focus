//
// Created by apin on 09.01.2025.
//

#include "Map.hpp"


using namespace vins::core;


void Map::add_keyframe(vins::core::KeyFrame *keyframe) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    std::lock_guard<std::mutex> write_lock(_write_mutex);
    keyframes[keyframe->id] = keyframe;
}

void Map::add_landmark(vins::core::Landmark *landmark) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    std::lock_guard<std::mutex> write_lock(_write_mutex);
    landmarks[landmark->id] = landmark;
}

void Map::remove_keyframe(uint64_t keyframe_id) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    std::lock_guard<std::mutex> write_lock(_write_mutex);
    keyframes.erase(keyframe_id);
}

void Map::remove_landmark(uint64_t landmark_id) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    std::lock_guard<std::mutex> write_lock(_write_mutex);
    landmarks.erase(landmark_id);
}

KeyFrame *Map::get_keyframe(uint64_t keyframe_id) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    return keyframes[keyframe_id];
}

Landmark *Map::get_landmark(uint64_t landmark_id) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    return landmarks[landmark_id];
}