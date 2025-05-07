#include "db_manager.hpp"

DBManager::DBManager(const std::string& conninfo)
{
    conn_ = std::make_unique<pqxx::connection>(conninfo);
    if (!conn_->is_open())
    {
        throw std::runtime_error("Failed to open database connection.");
    }
}

pqxx::connection& DBManager::connection()
{
    return *conn_;
}

bool DBManager::is_connected() const
{
    return conn_ && conn_->is_open();
}
