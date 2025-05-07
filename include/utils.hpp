#pragma once
#include <chrono>
#include <stdexcept>
#include <string>

std::string                           to_pg_date(const std::chrono::system_clock::time_point& tp);
std::chrono::system_clock::time_point from_pg_date(const std::string& str);
std::string                           extract_bank_id(const std::string& account_number);
