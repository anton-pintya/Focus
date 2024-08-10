#ifndef PRINT_INFO_HPP
#define PRINT_INFO_HPP


#include <iostream>
#include <cstdarg>
#include <cstdio>
#include <vector>

namespace vins_utils
{
    static void PRINT(const char* prefix, const char* format, ...)
    {
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

    #define VINS_INFO(fmt, ...) PRINT("\033[0;34mINFO: \033[0m", fmt, ##__VA_ARGS__)
    #define VINS_DEBUG(fmt, ...) PRINT("\033[0;33mDEBUG: \033[0m", fmt, ##__VA_ARGS__)
    #define VINS_ERROR(fmt, ...) PRINT("\033[0;31mERROR: \033[0m", fmt, ##__VA_ARGS__)

} // namespace vins_utils



#endif