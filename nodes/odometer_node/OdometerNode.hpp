//
// Created by apin on 10.01.2025.
//

#ifndef VINS_FOCUS_ODOMETERNODE_HPP
#define VINS_FOCUS_ODOMETERNODE_HPP


#include <memory>

#include "transport/Node.hpp"

#include "core/map/Map.hpp"

#include "sensors/soft_sensors/detector/FeatureDetector.hpp"
#include "sensors/soft_sensors/tracker/FeatureTracker.hpp"

#include "sensors/soft_sensors/detector/GridFeatureDetector.hpp"

#include "core/transport/Subscriber.hpp"
#include "core/transport/msg_generated/sensor_image.hpp"


namespace vins {
namespace nodes {

class OdometerNode : public core::transport::Node {

public:
    /*********Public fields*********/


    /*********Public methods*********/
    OdometerNode(const std::string &name, const cv::FileStorage& config);

    OdometerNode(const std::string &name, const cv::FileStorage& config, std::shared_ptr<vins::core::Map> map);

    void init() override;

    void add_map(std::shared_ptr<vins::core::Map> map);

    void configurate_detector(const cv::FileStorage& config);

    void configurate_tracker(const cv::FileStorage& config);

    void configurate_triangulator(const cv::FileStorage& config);

    cv::Mat get_last_image();

protected:
    /*********Protected fields*********/
    void run() override;

    /*********Protected methods*********/


private:
    /*********Private fields*********/
    vins::sensors::FeatureDetector  _detector{};
    vins::sensors::FeatureTracker   _tracker{};
//    vins::sensors::Triangulator   _triangulator;

    vins::sensors::GridFeatureDetector _grid_detector{};

    vins::core::transport::Subscriber<sensor_image> _image_sub;

    cv::FileStorage _config;

    std::shared_ptr<vins::core::Map> _map;

    cv::Mat _last_image;
    int _first_points_found{0};

    /*********Private methods*********/


};

}; //namespace nodes
}; //namespace vins

#endif //VINS_FOCUS_ODOMETERNODE_HPP
