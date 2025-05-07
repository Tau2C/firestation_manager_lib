#pragma once
#include <optional>
#include <string>
#include <vector>

#include "bank.hpp"
#include "db_manager.hpp"

class BankRepository
{
  public:
    explicit BankRepository(DBManager& db);

    std::vector<Bank>   get_all();
    std::optional<Bank> get_by_id(const std::string& id);
    void                insert(const Bank& b);
    void                update(const std::string id, const Bank& b);
    void                remove(const std::string& id);

  private:
    DBManager& db_;
};
