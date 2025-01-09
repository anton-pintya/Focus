#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "IMUGazeboHandler.hpp"
#include "libraries/mavlink/common/mavlink.h"
#include "utils/print_info.hpp"
#include <cstdlib>


using namespace vins::sensors;

IMUGazeboHandler::IMUGazeboHandler(cv::FileNode config) : _params(config) {

    config["type"] >> _connection_type;
    config["host"] >> _host;
    config["port"] >> _port;

    bool res = (_connection_type == "udp") ? _setup_udp_connection() : _setup_tcp_connection();

    if (!res) {
        std::exit(EXIT_FAILURE);
    }

    _load_calibration(config["calibration"]);
}


IMUGazeboHandler::~IMUGazeboHandler() {
    close(_sock);
}


bool IMUGazeboHandler::_setup_udp_connection() {

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = inet_addr(_host.c_str());
    _sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (_sock < 0) {
        vins_utils::VINS_ERROR("Failed to create UDP socket (%s:%i): %s", _host.c_str(), _port, strerror(errno));
        return false;
    }

    // Set the timeout for the connect function
    struct timeval timeout;
    timeout.tv_sec = (int )_params["timeout"];
    timeout.tv_usec = 0;

    if (setsockopt(_sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
        vins_utils::VINS_ERROR("Failed to set socket timeout options: %s", strerror(errno));
        close(_sock);
        return false;
    }

    uint8_t try_to_bind = bind(_sock, (struct sockaddr*)&_addr, sizeof(_addr));
    if (try_to_bind < 0) {
        vins_utils::VINS_ERROR("Failed to bind UDP socket (%s:%i): %s", _host.c_str(), _port, strerror(errno));
        close(_sock);
        return false;
    }

    return true;
}


bool IMUGazeboHandler::_setup_tcp_connection() {
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = inet_addr(_host.c_str());
    _sock = socket(AF_INET, SOCK_STREAM, 0);

    if (_sock < 0) {
        vins_utils::VINS_ERROR("Failed to create TCP socket (%s:%i): %s", _host.c_str(), _port, strerror(errno));
        return false;
    }

    // Set the timeout for the connect function
    struct timeval timeout;
    timeout.tv_sec = (int )_params["timeout"];
    timeout.tv_usec = 0;

    if (setsockopt(_sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
        vins_utils::VINS_ERROR("Failed to set socket timeout options: %s", strerror(errno));
        close(_sock);
        return false;
    }

    if (connect(_sock, (struct sockaddr*)&_addr, sizeof(_addr)) < 0) {
        vins_utils::VINS_ERROR("Failed to connect to TCP server (%s:%i): %s", _host.c_str(), _port, strerror(errno));
        close(_sock);
        return false;
    }

    return true;
}



void IMUGazeboHandler::read() {
    struct sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);
    int len = recvfrom(_sock, _buf, sizeof(_buf), 0, (struct sockaddr*)&src_addr, &addr_len);

    if (len > 0) {
        mavlink_message_t msg;
        mavlink_status_t status;

        for (int i = 0; i < len; ++i) {
            if (mavlink_parse_char(MAVLINK_COMM_0, _buf[i], &msg, &status)) {
                if (msg.msgid == MAVLINK_MSG_ID_HIL_SENSOR) {
                    mavlink_hil_sensor_t imu;
                    mavlink_msg_hil_sensor_decode(&msg, &imu);
                    _acc_data = {
                            .x = imu.xacc,
                            .y = imu.yacc,
                            .z = imu.zacc
                    };

                    _gyro_data = {
                            .x = imu.xgyro,
                            .y = imu.ygyro,
                            .z = imu.zgyro
                    };

                    publish();

                }
            }
        }
    }
//    else {
//        vins_utils::VINS_ERROR("Failed to receive data from %S socket: %s", _connection_type.c_str(), strerror(errno));
//    }

    memset(_buf, 0, sizeof(_buf));
}


void IMUGazeboHandler::print_info() {
    InertialSource::print_info();

    vins_utils::VINS_INFO("IMU Gazebo Handler");
    vins_utils::VINS_INFO("Connection type: %s", _connection_type.c_str());
    vins_utils::VINS_INFO("Host: %s", _host.c_str());
    vins_utils::VINS_INFO("Port: %i", _port);
//    vins_utils::VINS_INFO("Calibration:");
//    vins_utils::VINS_INFO("Accel:");
//    vins_utils::VINS_INFO("x: %f", _acc_data.x);
//    vins_utils::VINS_INFO("y: %f", _acc_data.y);
//    vins_utils::VINS_INFO("z: %f", _acc_data.z);
//    vins_utils::VINS_INFO("Gyro:");
//    vins_utils::VINS_INFO("x: %f", _gyro_data.x);
//    vins_utils::VINS_INFO("y: %f", _gyro_data.y);
//    vins_utils::VINS_INFO("z: %f", _gyro_data.z);
}
