#include "training_repository.hpp"
#include <pqxx/pqxx>

TrainingRepository::TrainingRepository(DBManager& db) : db_(db)
{
}

void TrainingRepository::insert(const Training& training)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("INSERT INTO trainings (name) VALUES ($1)", training.name);
    txn.commit();
}

std::vector<Training> TrainingRepository::get_all()
{
    pqxx::work txn(db_.connection());
    auto       result = txn.exec("SELECT training_id, name FROM trainings");

    std::vector<Training> trainings;
    for (const auto& row : result)
    {
        trainings.push_back({row[0].as<std::string>(), row[1].as<std::string>()});
    }
    return trainings;
}

std::optional<Training> TrainingRepository::get_by_id(std::string id)
{
    pqxx::work txn(db_.connection());
    auto       result =
        txn.exec_params("SELECT training_id, name FROM trainings WHERE training_id = $1", id);

    if (result.empty())
        return std::nullopt;
    return Training{result[0][0].as<std::string>(), result[0][1].as<std::string>()};
}

void TrainingRepository::update(const Training& training)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("UPDATE trainings SET name = $1 WHERE training_id = $2", training.name,
                    training.id);
    txn.commit();
}

void TrainingRepository::remove(std::string id)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("DELETE FROM trainings WHERE training_id = $1", id);
    txn.commit();
}
