#include "firefighter_training_repository.hpp"
#include "utils.hpp"
#include <pqxx/pqxx>

FirefighterTrainingRepository::FirefighterTrainingRepository(DBManager& db) : db_(db)
{
}

std::string FirefighterTrainingRepository::status_to_string(TrainingStatus status)
{
    return status == TrainingStatus::Valid ? "VALID" : "INVALID";
}

TrainingStatus FirefighterTrainingRepository::string_to_status(const std::string& s)
{
    return s == "VALID" ? TrainingStatus::Valid : TrainingStatus::Invalid;
}

void FirefighterTrainingRepository::insert(const FirefighterTraining& training)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("INSERT INTO firefighter_training (firefighter_id, training_id, date, "
                    "expiration, status) "
                    "VALUES ($1, $2, $3, $4, $5)",
                    training.firefighter_id, training.training_id, to_pg_date(training.date),
                    training.expiration ? to_pg_date(*training.expiration) : nullptr,
                    status_to_string(training.status));
    txn.commit();
}

std::optional<FirefighterTraining> FirefighterTrainingRepository::get_by_id(int id)
{
    pqxx::work txn(db_.connection());
    auto       result =
        txn.exec_params("SELECT id, firefighter_id, training_id, date, expiration, status "
                        "FROM firefighter_training WHERE id = $1",
                        id);

    if (result.empty())
        return std::nullopt;
    const auto& row = result[0];

    return FirefighterTraining{
        row["id"].as<int>(),
        row["firefighter_id"].as<int>(),
        row["training_id"].as<std::string>(),
        from_pg_date(row["date"].as<std::string>()),
        row["expiration"].is_null()
            ? std::nullopt
            : std::optional(from_pg_date(row["expiration"].as<std::string>())),
        string_to_status(row["status"].as<std::string>())};
}

std::vector<FirefighterTraining> FirefighterTrainingRepository::get_all()
{
    pqxx::work txn(db_.connection());
    auto       result = txn.exec("SELECT id, firefighter_id, training_id, date, "
                                       "expiration, status FROM firefighter_training");

    std::vector<FirefighterTraining> out;
    for (const auto& row : result)
    {
        out.push_back(FirefighterTraining{
            row["id"].as<int>(), row["firefighter_id"].as<int>(),
            row["training_id"].as<std::string>(), from_pg_date(row["date"].as<std::string>()),
            row["expiration"].is_null()
                ? std::nullopt
                : std::optional(from_pg_date(row["expiration"].as<std::string>())),
            string_to_status(row["status"].as<std::string>())});
    }
    return out;
}

void FirefighterTrainingRepository::update(const int id, const FirefighterTraining& training)
{
    pqxx::work txn(db_.connection());
    txn.exec_params(
        "UPDATE firefighter_training SET id = $6, firefighter_id = $1, training_id = $2, "
        "date = $3, expiration = $4, status = $5 "
        "WHERE id = $7",
        training.firefighter_id, training.training_id, to_pg_date(training.date),
        training.expiration ? to_pg_date(*training.expiration) : nullptr,
        status_to_string(training.status), training.id, id);
    txn.commit();
}

void FirefighterTrainingRepository::remove(int id)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("DELETE FROM firefighter_training WHERE id = $1", id);
    txn.commit();
}
