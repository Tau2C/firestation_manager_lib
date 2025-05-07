#pragma once
#include "db_manager.hpp"
#include "training.hpp"
#include <vector>

class TrainingRepository
{
  public:
    explicit TrainingRepository(DBManager& db);

    void                    insert(const Training& training);
    std::vector<Training>   get_all();
    std::optional<Training> get_by_id(std::string id);
    void                    update(const Training& training);
    void                    remove(std::string id);

  private:
    DBManager& db_;
};
