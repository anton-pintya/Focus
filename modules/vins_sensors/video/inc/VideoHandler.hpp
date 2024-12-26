#ifndef VIDEO_HANDLER_HPP
#define VIDEO_HANDLER_HPP

#include "VideoSource.hpp"
#include <opencv2/opencv.hpp>


namespace vins_sens
{
    class VideoHandler : public VideoSource
    {
        public:
            /*********Public fields*********/
            cv::VideoCapture video;             // <-

            std::string video_folder{""};
            std::string video_file{""};         // <- 

            /*********Public methods*********/
            VideoHandler(std::string config_path);

            /**
             * @brief Return DataPackage for given video source with available data for it
             * 
             * @return DataPackageBase 
             */
            DataPackageBase read() override;


            /**
             * @brief Print out in the terminal info about current video
             * 
             */
            void print_info() override;


        protected:
            /*********Protected fields*********/


            /*********Protected methods*********/


        private:
            /*********Private fields*********/


            /*********Private methods*********/


    };
}


#endif