//
// Created by apin on 27.12.2024.
//

#ifndef VINS_FOCUS_INERTIALSOURCE_HPP
#define VINS_FOCUS_INERTIALSOURCE_HPP

#include "vins_core/core.hpp"
#include "vins_core/topics/msg_generated/sensor_gyro.hpp"
#include "vins_core/topics/msg_generated/sensor_accel.hpp"

namespace vins_sens {

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
//            virtual int read() = 0;


            /**
             * @brief Publish DataPackage for given video source
             *
             * @return
             */
//            void publish(const int& pkg);


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

//            cv::Mat calibration;    // <- Calibration parameters for IMU sensor
            bool    has_gt{false};  // <- is ground-truth data available

            vins_core::Publisher<sensor_accel> acc_pub;  // <- Accelerometer publisher
            vins_core::Publisher<sensor_gyro> gyro_pub;  // <- Gyroscope publisher

            /*********Protected methods*********/

            /**
             * @brief Load calibration matrix for given dataset's sequence
             *
             * @param path - path to the dataset's calibration file (sequence.yaml)
             */
            void _load_calibration(std::string path);


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

} // vins_sens

#endif //VINS_FOCUS_INERTIALSOURCE_HPP
