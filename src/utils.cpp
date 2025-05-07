#include "utils.hpp"
#include <iomanip>
#include <sstream>

std::string to_pg_date(const std::chrono::system_clock::time_point& tp)
{
    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    std::tm     tm   = *std::gmtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

std::chrono::system_clock::time_point from_pg_date(const std::string& str)
{
    std::tm            tm = {};
    std::istringstream iss(str);
    iss >> std::get_time(&tm, "%Y-%m-%d");
    auto time = timegm(&tm);
    return std::chrono::system_clock::from_time_t(time);
}

std::string extract_bank_id(const std::string& account_number)
{
    if (account_number.size() < 6)
        throw std::invalid_argument("Account number too short");
    return account_number.substr(2, 4);
}
