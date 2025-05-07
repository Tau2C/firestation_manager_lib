#pragma once
#include <optional>
#include <string>

struct Firefighter
{
    int                        firefighter_id;
    std::string                name;
    std::string                surname;
    std::optional<std::string> address;
    std::optional<std::string> pesel;
    std::optional<std::string> phone;
    std::optional<std::string> account_number;
    std::optional<std::string> email;
};
