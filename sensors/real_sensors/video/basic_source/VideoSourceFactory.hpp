#ifndef VIDEO_SOURCE_FACTORY_HPP
#define VIDEO_SOURCE_FACTORY_HPP

#include "VideoSource.hpp"
#include "sensors/real_sensors/video/video_dataset/DatasetHandler.hpp"
#include "sensors/real_sensors/video/video_camera/CameraHandler.hpp"
#include "sensors/real_sensors/video/video_record/VideoHandler.hpp"
#include "sensors/real_sensors/video/video_stream/StreamHandler.hpp"

#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include <unistd.h>

#include "utils/print_info.hpp"


namespace vins {
namespace sensors {

using namespace vins_utils;

class VideoSourceFactory {
public:
    static std::unique_ptr<VideoSource> createVideoSource(const std::string config_path) {
        cv::FileStorage fs(config_path, cv::FileStorage::READ);

        if (!fs.isOpened()) {
            VINS_ERROR("Unable to open config file %s", config_path.c_str());
            return nullptr;
        }

        std::unique_ptr<VideoSource> source = createVideoSource(fs);

        fs.release();

        return source;
    }

    static std::unique_ptr<VideoSource> createVideoSource(const cv::FileStorage& config) {
        std::string source;
        config["general"]["source"] >> source;

        cv::FileNode node = config[source];

        if (source == "camera") {
            return std::unique_ptr<VideoSource>(
                    new CameraHandler(node)
            );
        } else if (source == "dataset") {
            return std::unique_ptr<VideoSource>(
                    new DatasetHandler(node)
            );
        } else if (source == "record") {
            return std::unique_ptr<VideoSource>(
                    new VideoHandler(node)
            );
        } else if (source == "stream") {
            return std::unique_ptr<VideoSource>(
                    new StreamHandler(node)
            );
        } else {
            VINS_ERROR("Unknown video source %s", source.c_str());
            return nullptr;
        }
    }

protected:
    /*********Protected fields*********/


    /*********Protected methods*********/


private:
    /*********Private fields*********/


    /*********Private methods*********/

};


}; // namespace sensors
}; // namespace vins



#endif