#include "utils.hpp"

std::string get_env(const char* name) {
    const char* val = std::getenv(name);
    if (!val) {
        throw std::runtime_error(std::string("Missing environment variable: ") + name);
    }
    return std::string(val);
}

std::string get_connection_string() {
    return "host=" + get_env("DB_HOST") +
           " dbname=" + get_env("DB_NAME") +
           " user=" + get_env("DB_USER") +
           " password=" + get_env("DB_PASSWORD") +
           " port=" + (std::getenv("DB_PORT") ? get_env("DB_PORT") : "5432");
}