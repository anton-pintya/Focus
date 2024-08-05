#ifndef DATASET_HANDLER_HPP
#define DATASET_HANDLER_HPP


#include <opencv2/opencv.hpp>
#include <iostream>


namespace vins_core
{

    struct DataPackage {
        float timestamp;                // <- time for given image
        cv::Vec<double, 3> coordinates; // <- vector = (x, y, z) in camera-frame
        cv::Mat rotation;               // <- temporary solution
        cv::Mat img;                    // <- image from dataset
    };

    /**
     * @brief Base class for handling datasets
     * 
     */ 
    class DatasetHandler
    {
        public:
            /*********Public fields*********/

            std::vector<std::string> images;    // <- Vector of sorted image filenames
            std::vector<float> times;           // <- Vector of "timestamps" for *.txt file
            cv::Mat calibration;                // <- Instrict params (3x3) for given camera (dataset)
            cv::Mat poses;                      // <- Ground-truth poses (now supports only KITTI structure)

            std::string data_source{"dataset"}; // <- Source of data (dataset | video | camera)
            int fps{30};                        // <- FPS value for given source

            /*********Public methods*********/

            /**
             * @brief Construct a new Dataset Handler object
             * 
             * @param configs_path - path to dataset's config file
             */
            DatasetHandler(std::string configs_path);

            /**
             * @brief Get the packed object for dataset's item
             * 
             * @param index - index of the dataset's item (img, timestamp, pose)
             * @return DataPackage 
             */
            DataPackage get_pack(int index);

            /**
             * @brief Overriden operator[] for getting access to dataset_item[i]
             * 
             * Alternative for DatasetHandler::get_pack(i) function
             * 
             * @param index - index of the dataset's item (img, timestamp, pose)
             * @return DataPackage 
             */
            DataPackage operator[](int index);


            int fps2ms() { return (int)(1e3 / fps); }

            void print_info();

        protected:
            /*********Protected fields*********/


            /*********Protected methods*********/


        private:
            /*********Private fields*********/


            /*********Private methods*********/

            /**
             * @brief Load sorted list of images for given dataset's sequence
             * 
             * @param path - path to the dataset's images 
             */
            void _load_images(std::string path);


            /**
             * @brief Load calibration matrix for given dataset's sequence
             * 
             * @param path - path to the dataset's calibration file (sequence.yaml)
             */
            void _load_calibration(std::string path);


            /**
             * @brief Load timestamps for given dataset's sequence
             * 
             * @param path  - path to dataset's timestamps file (sequence.txt)
             */
            void _load_times(std::string path);

            /**
             * @brief Load ground-truth poses for given dataset's sequence
             * 
             * @param path  - path to dataset's gt-poses file (sequence.txt)
             */
            void _load_poses(std::string path);

    };

} // namespace vins_core

#endif