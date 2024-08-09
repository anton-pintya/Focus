#ifndef VIDEO_SOURCE_HPP
#define VIDEO_SOURCE_HPP


#include <iostream>


namespace vins_core
{
    class VideoSource
    {
        public:
            virtual ~VideoSource() = default;

            // virtual void open() = 0;
            // virtual void read() = 0;
            // virtual void close() = 0

            virtual void print_info()
            {

            }

        protected:


        private:


    };
}


#endif