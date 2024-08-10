#ifndef CAMERA_HANDLER_HPP
#define CAMERA_HANDLER_HPP

#include "VideoSource.hpp"


namespace vins_core
{
    class CameraHandler : public VideoSource
    {
        public:
            /*********Public fields*********/


            /*********Public methods*********/
            CameraHandler(std::string configs_path);

            /**
             * @brief Return DataPackage for given video source with available data for it
             * 
             * @return DataPackageBase 
             */
            DataPackageBase read() override;

        protected:
            /*********Protected fields*********/


            /*********Protected methods*********/


        private:
            /*********Private fields*********/


            /*********Private methods*********/

    };
}


#endif