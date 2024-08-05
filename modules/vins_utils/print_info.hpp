#ifndef PRINT_INFO_HPP
#define PRINT_INFO_HPP


#include <iostream>
#include <cstdarg>
#include <cstdio>
#include <vector>
// #include <string>


namespace vins_utils
{
    
    void VINS_INFO(const char* format, ...) {
        const char* prefix = "INFO: ";
        std::vector<char> buffer(1024);

        va_list args;
        va_start(args, format);

        int needed = std::vsnprintf(buffer.data() + std::strlen(prefix), buffer.size() - std::strlen(prefix), format, args);
        if (needed >= buffer.size() - std::strlen(prefix)) {
            buffer.resize(needed + std::strlen(prefix) + 1);
            std::vsnprintf(buffer.data() + std::strlen(prefix), buffer.size() - std::strlen(prefix), format, args);
        }

        va_end(args);

        std::copy(prefix, prefix + std::strlen(prefix), buffer.data());
        std::printf("%s\n", buffer.data());
    }
} // namespace vins_utils



#endif