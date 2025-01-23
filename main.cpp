#include "utils/print_info.hpp"

#include "core/core.hpp"
#include "core/transport/msg_generated/sensor_image.hpp"
#include "core/transport/msg_generated/sensor_accel.hpp"

#include "nodes/imu_node/IMUNode.hpp"
#include "nodes/video_node/VideoNode.hpp"
#include "nodes/odometer_node/OdometerNode.hpp"

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
//    vins::core::transport::Subscriber<sensor_accel> acc_sub;

//    acc = acc_sub.receive();
//    vins::nodes::IMUNode imu_node(
//        "imu",
//        cv::FileStorage("./configs/imu.yaml", cv::FileStorage::READ)
//    );
//
//    imu_node.init();
//    imu_node.start();

    vins::nodes::VideoNode video_node(
        "video",
        cv::FileStorage("./configs/video.yaml", cv::FileStorage::READ)
    );

    video_node.init();
    video_node.start();

    vins::core::transport::Subscriber<sensor_image> sub_img;
    sub_img.subscribe();

    std::shared_ptr<vins::core::Map> map = std::make_shared<vins::core::Map>();

    vins::nodes::OdometerNode odometer_node(
        "odometer",
        cv::FileStorage("./configs/odometer.yaml", cv::FileStorage::READ),
        map
    );

    odometer_node.configurate_detector(
        cv::FileStorage("./configs/detector.yaml", cv::FileStorage::READ)
    );

    odometer_node.configurate_tracker(
            cv::FileStorage("./configs/tracker.yaml", cv::FileStorage::READ)
    );

    odometer_node.init();
    odometer_node.start();

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

        sensor_image msg = sub_img.receive();

        std::vector<cv::Mat> bgr(3);
        bgr[0] = cv::Mat(msg.height, msg.width, CV_8UC1, msg.r);
        bgr[1] = cv::Mat(msg.height, msg.width, CV_8UC1, msg.g);
        bgr[2] = cv::Mat(msg.height, msg.width, CV_8UC1, msg.b);

        cv::Mat image;
        cv::merge(bgr, image);

        vins::core::KeyFrame* keyframe = map->wait_untill_update();
        vins::core::KeyFrame* previous = keyframe->get_previous();

        if (previous == nullptr) {
            continue;
        }

        if (!image.empty()) {

            for (int i = 0; i < keyframe->keypoints.size(); i++) {
                cv::Point2f cur_pt = keyframe->keypoints[i].pt;
                cv::Point2f prev_pt = previous->keypoints[i].pt;

                cv::circle(
                        image,
                        cur_pt,
                        2,
                        cv::Scalar(255, 0, 0),
                        2
                );

                cv::line(
                        image,
                        cur_pt,
                        prev_pt,
                        cv::Scalar(0, 0, 255),
                        2
                );
            }

//            int x_step = image.cols / 5;
//            int y_step = image.rows / 5;
//
//            cv::Mat grid = cv::Mat::zeros(cv::Size{(int)(image.cols / x_step), (int)(image.rows / y_step)}, CV_8UC3);

//            for (int y = 0; y < grid.rows; y++) {
//                for (int x = 0; x < grid.cols; x++) {
//
//                    for (auto &kp: keyframe->keypoints) {
//                        if (kp.pt.x > (x * x_step) && kp.pt.x < ((x + 1) * x_step) &&
//                          kp.pt.y > (y * y_step) && kp.pt.y < ((y + 1) * y_step)) {
//                            grid.at<uint8_t>(x, y)++;
//                        }
//                    }
//
//                    cv::Scalar color(255 - grid.at<uint8_t>(x, y) * 5, grid.at<uint8_t>(x, y) * 5, 0);
//
//                    cv::rectangle(
//                            image,
//                            cv::Point{(int)(x * x_step), (int)(y * y_step)},
//                            cv::Point{(int)((x + 1) * x_step), (int)((y + 1) * y_step)},
//                            color,
//                            5, cv::FILLED
//                    );
//
//                    cv::putText(
//                            image,
//                            std::to_string(grid.at<uint8_t>(x, y)),
//                            cv::Point{(int)(x * x_step) + 15, (int)(y * y_step) + 20},
//                            cv::FONT_HERSHEY_SIMPLEX, 0.6,
//                            color,
//                            2, cv::LINE_AA
//                    );
//                }
//            }

//            cv::resize(grid, grid, cv::Size{x_step, y_step});

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
    std::exit(0);

    return 0;
}