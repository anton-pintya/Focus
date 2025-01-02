//
// Created by apin on 01.01.2025.
//

#ifndef VINS_FOCUS_IMUNODE_HPP
#define VINS_FOCUS_IMUNODE_HPP


#include "core/transport/Node.hpp"
#include "sensors/imu/imu.hpp"


namespace vins {

namespace nodes {

class IMUNode : public core::transport::Node {
public:
    /*********Public fields*********/


    /*********Public methods*********/
    IMUNode(const std::string &name, std::string config_path);

    void init() override;

protected:
    /*********Protected fields*********/


    /*********Protected methods*********/
    void run() override;


private:
    /*********Private fields*********/
    std::unique_ptr<sensors::InertialSource> _imu_source;

    /*********Private methods*********/


};

}; //namespace nodes

}; //namespace vins


#endif //VINS_FOCUS_IMUNODE_HPP
