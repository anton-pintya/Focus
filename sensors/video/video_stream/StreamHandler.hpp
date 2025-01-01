//
// Created by apin on 19.12.2024.
//

#ifndef VINS_FOCUS_STREAMHANDLER_H
#define VINS_FOCUS_STREAMHANDLER_H

#include "sensors/video/basic_source/VideoSource.hpp"


namespace vins {
    namespace sensors {

        class StreamHandler : public VideoSource {
        public:
            /*********Public fields*********/
            cv::VideoCapture video;

            std::string pipeline{""};

            /*********Public methods*********/
            StreamHandler(cv::FileNode config);

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
    }; //namespace sensors
}; //namespace vins

#endif //VINS_FOCUS_STREAMHANDLER_H
