#pragma once
#include "db_manager.hpp"
#include "firefighter_training.hpp"
#include <optional>
#include <vector>

class FirefighterTrainingRepository
{
  public:
    explicit FirefighterTrainingRepository(DBManager& db);

    void                               insert(const FirefighterTraining& training);
    std::optional<FirefighterTraining> get_by_id(int id);
    std::vector<FirefighterTraining>   get_all();
    void                               update(const int id, const FirefighterTraining& training);
    void                               remove(int id);

    std::string    status_to_string(TrainingStatus status);
    TrainingStatus string_to_status(const std::string& s);

  private:
    DBManager& db_;
};
