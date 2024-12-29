//
// Created by apin on 27.12.2024.
//

#include "vins_sensors/imu/imu.hpp"
#include "vins_utils/print_info.hpp"


using namespace vins_sens;
using namespace vins_utils;


void InertialSource::print_info() {
    VINS_INFO("INERTIAL SOURCE INFO");

    if (has_ground_truth()) {
        VINS_INFO("Ground-truth available");
    } else {
        VINS_ERROR("No available ground-truth data for given source or file");
    }

//    if (!calibration.empty()) {
//        VINS_INFO("Instric params:");
//        std::cout << calibration << std::endl;
//    } else {
//        VINS_ERROR("No available calibration data");
//    }
};