//
// Created by apin on 20.12.2024.
//

#ifndef VINS_FOCUS_SUBSCRIBER_HPP
#define VINS_FOCUS_SUBSCRIBER_HPP


#include <iostream>
#include <fcntl.h>           /* For O_* constants */
#include <sys/mman.h>        /* For shm_open */
#include <unistd.h>          /* For ftruncate */
#include <cstring>           /* For memset, strerror */
#include <string>
#include <stdexcept>


#include "vins_core/topics/Topic.hpp"


namespace vins_core {

    template<typename T>
    class Subscriber {
        public:
            /*********Public fields*********/


            /*********Public methods*********/
            explicit Subscriber() = default;

            T receive() {
                T data = _topic.get();
                return data;
            }


        protected:
            /*********Protected fields*********/


            /*********Protected methods*********/


        private:
            /*********Private fields*********/
            Topic<T> _topic;

            /*********Private methods*********/

    };

};



#endif //VINS_FOCUS_SUBSCRIBER_HPP
