#include "vins_core/video_source/VideoSourceFactory.hpp"
#include "vins_core/param_handler/ParamHandler.hpp"
#include "vins_core/video_source/DataPackageBase.hpp"

#include "vins_utils/print_info.hpp"

// using namespace vins_core;
// using namespace vins_utils;

int main(int argc, char** argv)
{
    std::unique_ptr<vins_core::VideoSource> video_source = 
        vins_core::VideoSourceFactory::createVideoSource(
            "./modules/vins_core/video_source/config.yaml"
        );

    video_source->print_info();

    vins_core::ParamHandler params("./modules/vins_core/param_handler/params.yaml");
    

    while (true)
    {
        vins_core::DataPackageBase pkg = video_source->read();

        if (!pkg.img.empty())
        {
            cv::imshow("Image", pkg.img);

            int key = cv::waitKey(video_source->fps_to_ms());

            if (key == 27) {
                return 0;
            }
        }
        
    }

    return 0;
}