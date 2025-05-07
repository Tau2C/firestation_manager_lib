#include "examination_type.hpp"
#include <stdexcept>

std::string to_string(ExaminationType type)
{
    switch (type)
    {
        case ExaminationType::FIREFIGHTER:
            return "FIREFIGHTER";
        case ExaminationType::DRIVER:
            return "DRIVER";
    }
    throw std::invalid_argument("Invalid ExaminationType");
}

ExaminationType to_examination_type(const std::string& str)
{
    if (str == "FIREFIGHTER")
        return ExaminationType::FIREFIGHTER;
    if (str == "DRIVER")
        return ExaminationType::DRIVER;
    throw std::invalid_argument("Unknown ExaminationType string: " + str);
}
