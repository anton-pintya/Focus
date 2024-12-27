#include "vins_sensors/video/video.hpp"
#include "vins_utils/print_info.hpp"

#include "vins_core/core.hpp"


int main(int argc, char** argv) {

    auto video_source = vins_sens::VideoSourceFactory::createVideoSource(
            "./modules/vins_sensors/video/config/config.yaml"
    );

    video_source->print_info();

    vins_core::Subscriber<sensor_image_gray> sub_img;

    while (true) {
        vins_sens::DataPackageBase pkg = video_source->read();
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