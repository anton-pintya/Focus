#ifndef VIDEO_SOURCE_FACTORY_HPP
#define VIDEO_SOURCE_FACTORY_HPP

#include "VideoSource.hpp"
#include "DatasetHandler.hpp"
#include "CameraHandler.hpp"
#include "VideoHandler.hpp"
#include "StreamHandler.hpp"

#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include <unistd.h>

#include "vins_utils/print_info.hpp"


namespace vins_sens
{
    using namespace vins_utils;

    class VideoSourceFactory
    {
        public:
            static std::unique_ptr<VideoSource> createVideoSource(const std::string config_path)
            {
                cv::FileStorage fs(config_path, cv::FileStorage::READ);

                if (!fs.isOpened()) {
                    VINS_ERROR("Unable to open config file %s", config_path.c_str());
                    return nullptr;
                }


                std::string video_source;

                fs["current"]["source"] >> video_source;

                if (video_source == "dataset") {
                    return std::unique_ptr<VideoSource>(
                            new DatasetHandler("../modules/vins_sensors/configurations/dataset_config.yaml")
                    );
                } else if (video_source == "video") {
                    return std::unique_ptr<VideoSource>(
                            new VideoHandler("../modules/vins_sensors/configurations/video_config.yaml")
                    );
                } else if (video_source == "camera") {
                    return std::unique_ptr<VideoSource>(
                            new CameraHandler("../modules/vins_sensors/configurations/camera_config.yaml")
                    );
                } else if (video_source == "stream") {
                    return std::unique_ptr<VideoSource>(
                            new StreamHandler("../modules/vins_sensors/configurations/stream_config.yaml")
                    );
                } else {
                    VINS_ERROR("Unknown video source: %s", video_source.c_str());
                }

                return nullptr;
            }

        protected:


        private:


    };

}



#endif