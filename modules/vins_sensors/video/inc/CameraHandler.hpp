#ifndef CAMERA_HANDLER_HPP
#define CAMERA_HANDLER_HPP

#include "VideoSource.hpp"


namespace vins_sens
{
    class CameraHandler : public VideoSource
    {
        public:
            /*********Public fields*********/

            cv::VideoCapture camera;            // <-
            int device_number{0};               // <- 

            /*********Public methods*********/
            CameraHandler(std::string configs_path);

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