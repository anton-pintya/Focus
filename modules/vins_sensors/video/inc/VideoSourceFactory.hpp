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

}



#endif