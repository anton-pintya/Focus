#ifndef VIDEO_SOURCE_FACTORY_HPP
#define VIDEO_SOURCE_FACTORY_HPP

#include "sensors/video/basic_source/VideoSource.hpp"
#include "sensors/video/video_dataset/DatasetHandler.hpp"
#include "sensors/video/video_camera/CameraHandler.hpp"
#include "sensors/video/video_record/VideoHandler.hpp"
#include "sensors/video/video_stream/StreamHandler.hpp"

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

                std::string video_source;
                fs["general"]["source"] >> video_source;

                cv::FileNode node = fs[video_source];

                if (video_source == "dataset") {
                    return std::unique_ptr<VideoSource>(
                            new DatasetHandler(node)
                    );
                } else if (video_source == "video") {
                    return std::unique_ptr<VideoSource>(
                            new VideoHandler(node)
                    );
                } else if (video_source == "camera") {
                    return std::unique_ptr<VideoSource>(
                            new CameraHandler(node)
                    );
                } else if (video_source == "stream") {
                    return std::unique_ptr<VideoSource>(
                            new StreamHandler(node)
                    );
                } else {
                    VINS_ERROR("Unknown video source: %s", video_source.c_str());
                }

                fs.release();

                return nullptr;
            }

        protected:


        private:


        };
    }; // namespace sensors
}; // namespace vins



#endif