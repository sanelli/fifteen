#pragma once

#include <stdexcept>
#include <string>

namespace fifteen
{
    struct fifteen_error
        : public std::logic_error
    {
        fifteen_error(const char* message) : std::logic_error(message){ };
    };
}