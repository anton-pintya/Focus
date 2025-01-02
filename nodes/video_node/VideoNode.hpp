//
// Created by apin on 02.01.2025.
//

#ifndef VINS_FOCUS_VIDEONODE_HPP
#define VINS_FOCUS_VIDEONODE_HPP


#include "core/transport/Node.hpp"
#include "sensors/video/video.hpp"


namespace vins {

namespace nodes {

    class VideoNode : public core::transport::Node {
    public:
        /*********Public fields*********/


        /*********Public methods*********/
        VideoNode(const std::string &name, std::string config_path);

        void init() override;

    protected:
        /*********Protected fields*********/


        /*********Protected methods*********/
        void run() override;


    private:
        /*********Private fields*********/
        std::unique_ptr<sensors::VideoSource> _imu_source;

        /*********Private methods*********/


    };

}; //namespace nodes

}; //namespace vins


#endif //VINS_FOCUS_VIDEONODE_HPP
