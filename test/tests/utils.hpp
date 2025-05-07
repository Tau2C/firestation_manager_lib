#pragma once
#include <cstdlib>
#include <stdexcept>
#include <string>

std::string get_env(const char* name);
std::string get_connection_string();
