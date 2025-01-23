//
// Created by apin on 09.01.2025.
//

#include "Map.hpp"


using namespace vins::core;


void Map::add_keyframe(vins::core::KeyFrame *keyframe) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    std::lock_guard<std::mutex> write_lock(_write_mutex);
    keyframes[keyframe->id] = keyframe;
    _latest_keyframe_id = keyframe->id;
    _new_added = true;
}

void Map::add_landmark(vins::core::Landmark *landmark) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    std::lock_guard<std::mutex> write_lock(_write_mutex);
    landmarks[landmark->id] = landmark;
    _latest_landmark_id = landmark->id;
}

void Map::remove_keyframe(uint64_t keyframe_id) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    std::lock_guard<std::mutex> write_lock(_write_mutex);
    keyframes.erase(keyframe_id);

    if (_latest_keyframe_id == keyframe_id) {
        _latest_keyframe_id = keyframes.end()->first;
    }
}

void Map::remove_landmark(uint64_t landmark_id) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    std::lock_guard<std::mutex> write_lock(_write_mutex);
    landmarks.erase(landmark_id);

    if (_latest_landmark_id == landmark_id) {
        _latest_landmark_id = landmarks.end()->first;
    }
}

KeyFrame* Map::get_keyframe(uint64_t keyframe_id) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    return keyframes[keyframe_id];
}

Landmark* Map::get_landmark(uint64_t landmark_id) {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    return landmarks[landmark_id];
}

KeyFrame* Map::get_latest_keyframe() {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    if (_latest_keyframe_id == UINT64_MAX)
        return nullptr;
    _new_added = false;
    return keyframes[_latest_keyframe_id];
}

Landmark* Map::get_latest_landmark() {
    std::lock_guard<std::mutex> read_lock(_read_mutex);
    if (_latest_landmark_id == UINT64_MAX)
        return nullptr;
    return landmarks[_latest_landmark_id];
}


KeyFrame* Map::wait_untill_update() {
    while(!_new_added) {}
    return get_latest_keyframe();
}