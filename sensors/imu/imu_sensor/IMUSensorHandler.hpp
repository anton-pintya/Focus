//
// Created by apin on 30.12.2024.
//

#ifndef VINS_FOCUS_IMUREALSENSOR_HPP
#define VINS_FOCUS_IMUREALSENSOR_HPP


#include <opencv2/opencv.hpp>

#include "sensors/imu/basic_source/InertialSource.hpp"


namespace vins {
namespace sensors {

class IMURealSensor : public InertialSource {

    public:
        /*********Public fields*********/


        /*********Public methods*********/
        IMURealSensor(cv::FileNode config);


//        void read() override;
//
//        void print_info() override;

    protected:
        /*********Protected fields*********/


        /*********Protected methods*********/


    private:
        /*********Private fields*********/


        /*********Private methods*********/


};

}; // namespace sensors
}; // namespace vins


#endif //VINS_FOCUS_IMUREALSENSOR_HPP
