#include "utils/print_info.hpp"

#include "core/core.hpp"
#include "core/transport/msg_generated/sensor_image_gray.hpp"

#include "nodes/imu_node/IMUNode.hpp"
#include "nodes/video_node/VideoNode.hpp"

#include "sensors/soft_sensors/detector/FeatureDetector.hpp"
#include "core/map/Map.hpp"


/*
 * Needed to launch and debug the integrator node (currently disabled
 * because of incorrect implementation of the node)
 **/
//#define WITH_TIMEOUT

#ifdef WITH_TIMEOUT
#define TIMEOUT 50
#endif

/* Needed to debug program for short time-period */
//#define PRINT_IMU

#ifdef PRINT_IMU
#include "sensors/real_sensors/video/video.hpp"
#include "sensors/real_sensors/imu/imu.hpp"
#endif

/* Needed to debug IMU node and Pub-Sub transport layer */
//#define LAUNCH_INTEGRATOR

#ifdef LAUNCH_INTEGRATOR
#include "nodes/integrator_node/IntegratorNode.hpp"
#endif



int main(int argc, char** argv) {

    vins::nodes::IMUNode imu_node("imu", "./sensors/real_sensors/imu/config/config.yaml");

    imu_node.init();
    imu_node.start();

    vins::nodes::VideoNode video_node("video", "./sensors/real_sensors/video/config/config.yaml");

    video_node.init();
    video_node.start();

    vins::core::transport::Subscriber<sensor_accel> sub_accel;
    vins::core::transport::Subscriber<sensor_gyro> sub_gyro;
    vins::core::transport::Subscriber<sensor_image_gray> sub_img;

    std::shared_ptr<vins::core::Map> map = std::make_shared<vins::core::Map>();

    vins::sensors::FeatureDetector detector(
        cv::FileStorage("./sensors/soft_sensors/detector/config/config.yaml", cv::FileStorage::READ),
        map
    );

/*
 * Needed to launch and debug the integrator node (currently disabled
 * because of incorrect implementation of the node)
 **/
#ifdef LAUNCH_INTEGRATOR
    vins::nodes::IntegratorNode integrator_node("integrator");

    integrator_node.init();
    integrator_node.start();
#endif

/* Needed to debug program for short time-period */
#ifdef WITH_TIMEOUT
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(TIMEOUT)) {
#else
    while (true) {
#endif

/* Needed to debug IMU node and Pub-Sub transport layer */
#ifdef PRINT_IMU
        sensor_accel accel = sub_accel.receive();
        vins_utils::VINS_INFO("Accel: %f %f %f", accel.x, accel.y, accel.z);

        sensor_gyro gyro = sub_gyro.receive();
        vins_utils::VINS_INFO("Gyro: %f %f %f", gyro.x, gyro.y, gyro.z);
#endif

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
#ifdef WITH_TIMEOUT
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
#endif
    }

    cv::destroyAllWindows();

    return 0;
}