#pragma once
#include <chrono>
#include <optional>
#include <string>

enum class TrainingStatus
{
    Valid,
    Invalid
};

struct FirefighterTraining
{
    int                                                  id;
    int                                                  firefighter_id;
    std::string                                          training_id;
    std::chrono::system_clock::time_point                date;
    std::optional<std::chrono::system_clock::time_point> expiration;
    TrainingStatus                                       status;
};
