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


        ~IMUGazeboHandler() override;


        void read() override;


        void print_info() override;

    protected:
        /*********Protected fields*********/


        /*********Protected methods*********/


    private:
        /*********Private fields*********/
        cv::FileNode _params;

        std::string _connection_type;
        std::string _host;
        int _port;

        struct sockaddr_in _addr;
        int _sock;
        uint8_t _buf[2048]{0};

        /*********Private methods*********/
        bool _setup_udp_connection();

        bool _setup_tcp_connection();

    };

}; //namespace sensors
}; //namespace vins


#endif //VINS_FOCUS_IMUSIMULATORGAZEBO_HPP
