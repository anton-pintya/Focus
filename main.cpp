#include "sensors/video/video.hpp"
#include "sensors/imu/imu.hpp"
#include "utils/print_info.hpp"

#include "core/core.hpp"
#include "core/transport/msg_generated/sensor_image_gray.hpp"

#include "nodes/imu_node/IMUNode.hpp"
#include "nodes/video_node/VideoNode.hpp"


#define TIMEOUT 50


int main(int argc, char** argv) {

    vins::nodes::IMUNode imu_node("imu", "./sensors/imu/config/config.yaml");

    imu_node.init();
    imu_node.start();

    vins::nodes::VideoNode video_node("video", "./sensors/video/config/config.yaml");

    video_node.init();
    video_node.start();

    vins::core::transport::Subscriber<sensor_accel> sub_accel;
    vins::core::transport::Subscriber<sensor_gyro> sub_gyro;
    vins::core::transport::Subscriber<sensor_image_gray> sub_img;

    auto start = std::chrono::steady_clock::now();

//    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(TIMEOUT)) {
    while (true) {
        sensor_accel accel = sub_accel.receive();
        vins_utils::VINS_INFO("Accel: %f %f %f", accel.x, accel.y, accel.z);

        sensor_gyro gyro = sub_gyro.receive();
        vins_utils::VINS_INFO("Gyro: %f %f %f", gyro.x, gyro.y, gyro.z);

        sensor_image_gray img = sub_img.receive();

        cv::Mat image = cv::Mat(img.height, img.width, CV_8UC1, img.data);

        if (!image.empty()) {
            cv::imshow("Image", image);

            int key = cv::waitKey(30);

            if (key == 27) {
                break;
            }
        } else {
            vins_utils::VINS_DEBUG("Image is empty");
        }

//        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    cv::destroyAllWindows();

    return 0;
}