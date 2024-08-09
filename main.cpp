#include "vins_core/video_source/VideoSourceFactory.hpp"
#include "vins_core/param_handler/ParamHandler.hpp"

#include "vins_utils/print_info.hpp"

// using namespace vins_core;
// using namespace vins_utils;

int main(int argc, char** argv)
{
    // vins_core::DatasetHandler dataset("./modules/vins_core/dataset_handler/config.yaml");
    // dataset.print_info();


    auto video_source = 
        vins_core::VideoSourceFactory::createVideoSource(
            "./modules/vins_core/video_source/config.yaml"
        );

    video_source->print_info();

    vins_core::ParamHandler params("./modules/vins_core/param_handler/params.yaml");
    
    // for (int i = 0; i < dataset.images.size(); i++)
    // {
    //     vins_core::DataPackage pkg = dataset[i];

    //     std::cout << pkg.coordinates << std::endl;

    //     cv::imshow("Image", pkg.img);

    //     int key = cv::waitKey(dataset.fps_to_ms());

    //     if (key == 27) {
    //         return 0;
    //     }
    // }

    return 0;
}