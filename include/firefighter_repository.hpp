#pragma once
#include "db_manager.hpp"
#include "firefighter.hpp"
#include <optional>
#include <vector>

class FirefighterRepository
{
  public:
    explicit FirefighterRepository(DBManager& db);

    std::vector<Firefighter>   get_all();
    std::optional<Firefighter> get_by_id(int id);
    void                       insert(const int id, const Firefighter& f);
    void                       insert(const Firefighter& f);
    void                       update(const int id, const Firefighter& f);
    void                       remove(int id);

  private:
    DBManager& db_;
};
