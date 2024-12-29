//
// Created by apin on 29.12.2024.
//

#ifndef VINS_FOCUS_INERTIALSOURCEFACTORY_HPP
#define VINS_FOCUS_INERTIALSOURCEFACTORY_HPP


#include <memory>
#include <opencv2/opencv.hpp>

#include "vins_utils/print_info.hpp"


namespace vins_sens {

    using namespace vins_utils;

    class InertialSourceFactory {
        public:
            /*********Public fields*********/
            static std::unique_ptr<InertialSource> createInertialSource(const std::string config_path) {

                cv::FileStorage fs(config_path, cv::FileStorage::READ);

                if (!fs.isOpened()) {
                    VINS_ERROR("Unable to open config file %s", config_path.c_str());
                    return nullptr;
                }

                std::string source;
                fs["general"]["source"] >> source;

                cv::FileNode node = fs[source];

                if (source == "sensor") {
                    return std::unique_ptr<InertialSource>(
                            nullptr
                    );
                } else if (source == "gazebo") {
                    return std::unique_ptr<InertialSource>(
                            nullptr
                    );
                } else {
                    VINS_ERROR("Unknown IMU source: %s", source.c_str());
                }

                fs.release();

                return nullptr;
            }


            /*********Public methods*********/


        protected:
            /*********Protected fields*********/


            /*********Protected methods*********/


        private:
            /*********Private fields*********/


            /*********Private methods*********/

    };

}

#endif //VINS_FOCUS_INERTIALSOURCEFACTORY_HPP
