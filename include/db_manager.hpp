#pragma once
#include <memory>
#include <pqxx/pqxx>
#include <string>

class DBManager
{
  public:
    explicit DBManager(const std::string& conninfo);
    pqxx::connection& connection();
    bool              is_connected() const;

  private:
    std::unique_ptr<pqxx::connection> conn_;
};
