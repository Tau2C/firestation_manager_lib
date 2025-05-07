#include "firefighter_repository.hpp"
#include <pqxx/pqxx>

FirefighterRepository::FirefighterRepository(DBManager& db) : db_(db)
{
}

std::vector<Firefighter> FirefighterRepository::get_all()
{
    pqxx::work   txn(db_.connection());
    pqxx::result res = txn.exec("SELECT firefighter_id, name, surname, address, "
                                "pesel, phone, account_number, email FROM firefighters "
                                "ORDER BY firefighter_id;");

    std::vector<Firefighter> result;
    for (const auto& row : res)
    {
        result.push_back(Firefighter{
            .firefighter_id = row[0].as<int>(),
            .name           = row[1].as<std::string>(),
            .surname        = row[2].as<std::string>(),
            .address = row[3].is_null() ? std::nullopt : std::optional(row[3].as<std::string>()),
            .pesel   = row[4].is_null() ? std::nullopt : std::optional(row[4].as<std::string>()),
            .phone   = row[5].is_null() ? std::nullopt : std::optional(row[5].as<std::string>()),
            .account_number =
                row[6].is_null() ? std::nullopt : std::optional(row[6].as<std::string>()),
            .email = row[7].is_null() ? std::nullopt : std::optional(row[7].as<std::string>())});
    }
    return result;
}

std::optional<Firefighter> FirefighterRepository::get_by_id(int id)
{
    pqxx::work   txn(db_.connection());
    pqxx::result res =
        txn.exec_params("SELECT firefighter_id, name, surname, address, pesel, phone, "
                        "account_number email FROM firefighters WHERE firefighter_id = $1",
                        id);

    if (res.empty())
        return std::nullopt;

    const auto& row = res[0];
    return std::optional(Firefighter{
        .firefighter_id = row[0].as<int>(),
        .name           = row[1].as<std::string>(),
        .surname        = row[2].as<std::string>(),
        .address        = row[3].is_null() ? std::nullopt : std::optional(row[3].as<std::string>()),
        .pesel          = row[4].is_null() ? std::nullopt : std::optional(row[4].as<std::string>()),
        .phone          = row[5].is_null() ? std::nullopt : std::optional(row[5].as<std::string>()),
        .account_number = row[6].is_null() ? std::nullopt : std::optional(row[6].as<std::string>()),
        .email = row[7].is_null() ? std::nullopt : std::optional(row[7].as<std::string>())});
}

void FirefighterRepository::insert(const Firefighter& f)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("INSERT INTO firefighters (name, surname, address, pesel, "
                    "phone, account_number) VALUES ($1, $2, $3, $4, $5, $6)",
                    f.name, f.surname, f.address, f.pesel, f.phone, f.account_number);
    txn.commit();
}

void FirefighterRepository::insert(const int id, const Firefighter& f)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("INSERT INTO firefighters (firefighter_id, name, surname, "
                    "address, pesel, "
                    "phone, account_number) VALUES ($7, $1, $2, $3, $4, $5, $6)",
                    f.name, f.surname, f.address, f.pesel, f.phone, f.account_number, id);
    txn.commit();
}

void FirefighterRepository::update(const int id, const Firefighter& f)
{
    pqxx::work txn(db_.connection());
    txn.exec_params(
        "UPDATE firefighters SET firefighter_id=$7, name=$1, surname=$2, address=$3, pesel=$4, "
        "phone=$5, account_number=$6 WHERE firefighter_id=$8",
        f.name, f.surname, f.address, f.pesel, f.phone, f.account_number, f.firefighter_id, id);
    txn.commit();
}

void FirefighterRepository::remove(int id)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("DELETE FROM firefighters WHERE firefighter_id=$1", id);
    txn.commit();
}
