#ifndef DATA_PACKAGE_BASE
#define DATA_PACKAGE_BASE

#include <opencv2/opencv.hpp>


namespace vins_sens
{
    /**
     * @brief Perform a basic package for monocular visual odometry dataset
     * 
     */
    struct DataPackageBase
    {
        double timestamp{0};             // <- time for given image
        cv::Mat img;                    // <- image from dataset
    };

    
    struct DatasetPackage: public DataPackageBase
    {
        cv::Vec<double, 3> coordinates; // <- vector = (x, y, z) in camera-frame
        cv::Mat rotation;               // <- temporary solution
    };
    

    struct VideoPackage: public DataPackageBase
    {
        cv::Vec<double, 3> coordinates; // <- optional
        cv::Mat rotation;               // <- optional
    };


    struct CameraPackage: public DataPackageBase
    {  };
    


} // namespace vins_sensors


#endif