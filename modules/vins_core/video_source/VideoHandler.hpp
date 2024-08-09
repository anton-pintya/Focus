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
            std::vector<std::string> images;    // <- 
            std::vector<float> times;           // <- 
            cv::Mat calibration;                // <- 
            cv::Mat poses;                      // <- 

            std::string video_folder{""};
            std::string video_file{""};         // <- 
            int fps{30};

            /*********Public methods*********/
            VideoHandler(std::string configs_path); 


        protected:
            /*********Protected fields*********/


            /*********Protected methods*********/


        private:
            /*********Private fields*********/


            /*********Private methods*********/


    };
}


#endif