//
// Created by apin on 27.12.2024.
//

#include "sensors/imu/imu.hpp"
#include "utils/print_info.hpp"


using namespace vins::sensors;
using namespace vins_utils;


void InertialSource::print_info() {
    VINS_INFO("INERTIAL SOURCE INFO");

    if (has_ground_truth()) {
        VINS_INFO("Ground-truth available");
    } else {
        VINS_ERROR("No available ground-truth data for given source or file");
    }

    if (_accel_offset != 0) {
        VINS_INFO("IMU calibration loaded");
        VINS_INFO("Accelerometer offset: %f %f %f", _accel_offset[0], _accel_offset[1], _accel_offset[2]);
    } else {
        VINS_ERROR("No available calibration data");
    }
};


void InertialSource::publish() {
    _acc_pub.publish(_acc_data);
    _gyro_pub.publish(_gyro_data);
}


void InertialSource::_load_calibration(std::string path) {
    cv::FileStorage calib_file(path, cv::FileStorage::READ);

    if (!calib_file.isOpened()) {
        VINS_ERROR("Unable to open file %s", path.c_str());
        return;
    }

    calib_file["accel_noise_density"] >> _accel_noise_density;
    calib_file["accel_random_walk"] >>   _accel_random_walk;
    calib_file["accel_offset"][0] >>     _accel_offset[0];
    calib_file["accel_offset"][1] >>     _accel_offset[1];
    calib_file["accel_offset"][2] >>     _accel_offset[2];
    calib_file["accel_scale"][0] >>      _accel_scale[0];
    calib_file["accel_scale"][1] >>      _accel_scale[1];
    calib_file["accel_scale"][2] >>      _accel_scale[2];

    calib_file["gyro_noise_density"] >>  _gyro_noise_density;
    calib_file["gyro_random_walk"] >>    _gyro_random_walk;
    calib_file["gyro_offset"][0] >>      _gyro_offset[0];
    calib_file["gyro_offset"][1] >>      _gyro_offset[1];
    calib_file["gyro_offset"][2] >>      _gyro_offset[2];
    calib_file["gyro_scale"][0] >>       _gyro_scale[0];
    calib_file["gyro_scale"][1] >>       _gyro_scale[1];
    calib_file["gyro_scale"][2] >>       _gyro_scale[2];

    calib_file.release();
}


void InertialSource::_load_calibration(cv::FileNode calibration) {

    calibration["accel_noise_density"] >> _accel_noise_density;
    calibration["accel_random_walk"] >>   _accel_random_walk;
    calibration["accel_offset"][0] >>     _accel_offset[0];
    calibration["accel_offset"][1] >>     _accel_offset[1];
    calibration["accel_offset"][2] >>     _accel_offset[2];
    calibration["accel_scale"][0] >>      _accel_scale[0];
    calibration["accel_scale"][1] >>      _accel_scale[1];
    calibration["accel_scale"][2] >>      _accel_scale[2];

    calibration["gyro_noise_density"] >>  _gyro_noise_density;
    calibration["gyro_random_walk"] >>    _gyro_random_walk;
    calibration["gyro_offset"][0] >>      _gyro_offset[0];
    calibration["gyro_offset"][1] >>      _gyro_offset[1];
    calibration["gyro_offset"][2] >>      _gyro_offset[2];
    calibration["gyro_scale"][0] >>       _gyro_scale[0];
    calibration["gyro_scale"][1] >>       _gyro_scale[1];
    calibration["gyro_scale"][2] >>       _gyro_scale[2];
}


double InertialSource::_get_time_since_last_call()
{
    static auto last_call_time = std::chrono::steady_clock::now();

    auto current_time = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_time = current_time - last_call_time;

    last_call_time = current_time;

    return elapsed_time.count();
}


double InertialSource::_get_time_since_first_call()
{
    static double time_passed = 0;
    time_passed += _get_time_since_last_call();
    return time_passed;
}