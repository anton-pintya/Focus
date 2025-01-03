//
// Created by apin on 27.12.2024.
//

#ifndef VINS_FOCUS_INERTIALSOURCE_HPP
#define VINS_FOCUS_INERTIALSOURCE_HPP


#include "core/core.hpp"
#include "core/transport/msg_generated/sensor_accel.hpp"
#include "core/transport/msg_generated/sensor_gyro.hpp"

#include <opencv2/opencv.hpp>

namespace vins {
namespace sensors {

    class InertialSource {
    public:
        /*********Public fields*********/



        /*********Public methods*********/

        virtual ~InertialSource() = default;

        /**
         * @brief Return DataPackage for given video source with available data for it
         *
         * @return DataPackageBase
         */
        virtual void read() = 0;


        /**
         * @brief Publish DataPackage for given video source
         *
         * @return
         */
        void publish();


        /**
         * @brief Return True if ground-truth data is available for given video source
         *
         * @return true - ground-truth available
         * @return false - ground-truth unavailable
         */
        virtual bool has_ground_truth() { return has_gt; }


        /**
         * @brief Print out in the terminal info about current dataset (or source) used
         *
         */
        virtual void print_info();

    protected:
        /*********Protected fields*********/
        float _accel_noise_density = 2.0000e-3;                 //<- [ m / s^2 / sqrt(Hz) ]   ( accel "white noise" )
        float _accel_random_walk = 3.0000e-3;                   //<- [ m / s^3 / sqrt(Hz) ].  ( accel bias diffusion )
        float _accel_scale[3] = {1.0, 1.0, 1.0};
        float _accel_offset[3] = {0.0, 0.0, 0.0};

        float _gyro_noise_density = 1.6968e-04;                 //<- [ rad / s / sqrt(Hz) ]   ( gyro "white noise" )
        float _gyro_random_walk = 1.9393e-05;                   //<- [ rad / s^2 / sqrt(Hz) ] ( gyro bias diffusion )
        float _gyro_scale[3] = {1.0, 1.0, 1.0};
        float _gyro_offset[3] = {0.0, 0.0, 0.0};

        bool has_gt{false};  // <- is ground-truth data available

        sensor_accel _acc_data;  // <- Accelerometer data
        sensor_gyro _gyro_data;  // <- Gyroscope data

        vins::core::transport::Publisher<sensor_accel> _acc_pub;  // <- Accelerometer publisher
        vins::core::transport::Publisher<sensor_gyro> _gyro_pub;  // <- Gyroscope publisher

        /*********Protected methods*********/

        /**
         * @brief Load calibration matrix for given dataset's sequence
         *
         * @param path - path to the dataset's calibration file (sequence.yaml)
         */
        void _load_calibration(std::string path);

        void _load_calibration(cv::FileNode calibration);


        /**
         * @brief Return number of seconds since function had been called
         *
         * @return double
         */
        double _get_time_since_last_call();


        /**
         * @brief Return number of seconds since function had been called first time
         *
         * @return double
         */
        double _get_time_since_first_call();


    private:
        /*********Private fields*********/


        /*********Private methods*********/


    };

}; // namespace sensors
}; // namespace vins

#endif //VINS_FOCUS_INERTIALSOURCE_HPP
