#pragma once
#include <string>

enum class ExaminationType
{
    FIREFIGHTER,
    DRIVER
};

std::string     to_string(ExaminationType type);
ExaminationType to_examination_type(const std::string& str);
