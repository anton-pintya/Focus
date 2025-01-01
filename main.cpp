#include "sensors/video/video.hpp"
#include "sensors/imu/imu.hpp"
#include "utils/print_info.hpp"

#include "core/core.hpp"
#include "core/transport/msg_generated/sensor_image_gray.hpp"

#include <thread>

int main(int argc, char** argv) {

    auto video_source = vins::sensors::VideoSourceFactory::createVideoSource(
            "./sensors/video/config/config.yaml"
    );

    if (video_source == nullptr) {
        vins_utils::VINS_ERROR("Failed to instantiate video source");
        return -1;
    } else {
        video_source->print_info();
    }

    auto imu_source = vins::sensors::InertialSourceFactory::createInertialSource(
        "./sensors/imu/config/config.yaml"
    );

    if (imu_source == nullptr) {
        vins_utils::VINS_ERROR("Failed to instantiate inertial source");
        return -1;
    } else {
        imu_source->print_info();
    }

    vins::core::transport::Subscriber<sensor_image_gray> sub_img;

    while (true) {
        imu_source->read();

        video_source->read();
        sensor_image_gray img = sub_img.receive();

        cv::Mat image = cv::Mat(img.height, img.width, CV_8UC1, img.data);

        if (!image.empty()) {
            cv::imshow("Image", image);

            int key = cv::waitKey(video_source->fps_to_ms());

            if (key == 27) {
                break;
            }
        } else {
            vins_utils::VINS_DEBUG("Image is empty");
        }
    }

    return 0;
}