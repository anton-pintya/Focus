//
// Created by apin on 30.12.2024.
//

#ifndef VINS_FOCUS_IMUSIMULATORGAZEBO_HPP
#define VINS_FOCUS_IMUSIMULATORGAZEBO_HPP


#include <opencv2/opencv.hpp>
#include "sensors/imu/basic_source/InertialSource.hpp"


#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <pthread.h>
#include <sys/socket.h>
#include <termios.h>
#include <arpa/inet.h>


namespace vins {
namespace sensors {

    class IMUGazeboHandler : public InertialSource {
    public:
        /*********Public fields*********/


        /*********Public methods*********/
        IMUGazeboHandler(cv::FileNode config);


        void read() override;


//        void print_info() override;

    protected:
        /*********Protected fields*********/


        /*********Protected methods*********/


    private:
        /*********Private fields*********/
        struct sockaddr_in _addr;
        int _sock;
        uint8_t _buf[2048]{0};

        /*********Private methods*********/


    };

}; //namespace sensors
}; //namespace vins


#endif //VINS_FOCUS_IMUSIMULATORGAZEBO_HPP
