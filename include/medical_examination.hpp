#pragma once
#include "examination_type.hpp"
#include <chrono>

struct MedicalExamination
{
    int                                   id;
    ExaminationType                       type;
    int                                   firefighter_id;
    std::chrono::system_clock::time_point date;
    std::chrono::system_clock::time_point expiration;
};
