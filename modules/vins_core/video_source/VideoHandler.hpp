#ifndef VIDEO_HANDLER_HPP
#define VIDEO_HANDLER_HPP

#include "VideoSource.hpp"
#include <opencv2/opencv.hpp>


namespace vins_core
{
    class VideoHandler : public VideoSource
    {
        public:
            /*********Public fields*********/
            cv::VideoCapture video;             // <-
            std::vector<float> times;           // <- 
            cv::Mat calibration;                // <- 
            cv::Mat poses;                      // <- 

            std::string video_folder{""};
            std::string video_file{""};         // <- 

            /*********Public methods*********/
            VideoHandler(std::string configs_path); 

            /**
             * @brief Return DataPackage for given video source with available data for it
             * 
             * @return DataPackageBase 
             */
            DataPackageBase read() override;


        protected:
            /*********Protected fields*********/


            /*********Protected methods*********/


        private:
            /*********Private fields*********/


            /*********Private methods*********/


    };
}


#endif