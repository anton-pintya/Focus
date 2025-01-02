#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "IMUGazeboHandler.hpp"
#include "libraries/mavlink/common/mavlink.h"
#include "utils/print_info.hpp"

using namespace vins::sensors;

IMUGazeboHandler::IMUGazeboHandler(cv::FileNode config) {
    _load_calibration(config["calibration"]);

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(19856); // Используйте другой порт
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (_sock < 0) {
        vins_utils::VINS_ERROR("Failed to create UDP socket: %s", strerror(errno));
        return;
    }

    if (bind(_sock, (struct sockaddr*)&_addr, sizeof(_addr)) < 0) {
        vins_utils::VINS_ERROR("Failed to bind UDP socket: %s", strerror(errno));
        close(_sock);
        return;
    }
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

                } else {
                    vins_utils::VINS_ERROR("Received unknown message with id %d", msg.msgid);
                }
            }
        }
    } else {
        vins_utils::VINS_ERROR("Failed to receive data from UDP socket: %s", strerror(errno));
    }

    memset(_buf, 0, sizeof(_buf));
}

