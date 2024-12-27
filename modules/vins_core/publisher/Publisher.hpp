//
// Created by apin on 20.12.2024.
//

#ifndef VINS_FOCUS_PUBLISHER_HPP
#define VINS_FOCUS_PUBLISHER_HPP

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
    class Publisher {

        public:
            /*********Public fields*********/


            /*********Public methods*********/
            explicit Publisher() = default;

            void publish(const T& data) {
                _topic.post(data);
            }


        protected:
            /*********Protected fields*********/


            /*********Protected methods*********/


        private:
            /*********Private fields*********/
            Topic<T> _topic;


            /*********Private methods*********/

    };

}


#endif //VINS_FOCUS_PUBLISHER_HPP
