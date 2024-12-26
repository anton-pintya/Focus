#ifndef VIDEO_SOURCE_HPP
#define VIDEO_SOURCE_HPP


#include <iostream>
#include "DataPackageBase.hpp"

namespace vins_sens
{
    class VideoSource
    {
        public:
            /*********Public fields*********/

            

            /*********Public methods*********/

            virtual ~VideoSource() = default;
            
            /**
             * @brief Return DataPackage for given video source with available data for it
             * 
             * @return DataPackageBase 
             */
            virtual DataPackageBase read() = 0;


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


            /**
             * @brief Convert given camera FPS to millisecond for cv::waitkey(delay_ms)
             * 
             * @return int - delay in milliseconds 
             */
            int fps_to_ms() { return (int)(1e3 / fps); }

        protected:
            /*********Protected fields*********/

            cv::Mat calibration;    // <- Instrict params (3x3) for given camera (dataset)
            cv::Mat poses;          // <- Ground-truth poses (now supports only KITTI structure)

            bool    has_gt{false};  // <- is ground-truth data available
            int     fps{30};        // <- FPS value for given source

            /*********Protected methods*********/

            /**
             * @brief Load calibration matrix for given dataset's sequence
             * 
             * @param path - path to the dataset's calibration file (sequence.yaml)
             */
            void _load_calibration(std::string path);


            /**
             * @brief Load ground-truth poses for given dataset's sequence
             * 
             * @param path  - path to dataset's gt-poses file (sequence.txt)
             */
            void _load_poses(std::string path);


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
}


#endif