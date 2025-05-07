#include "bank_repository.hpp"
#include <pqxx/pqxx>

BankRepository::BankRepository(DBManager& db) : db_(db)
{
}

std::vector<Bank> BankRepository::get_all()
{
    pqxx::work   txn(db_.connection());
    pqxx::result res = txn.exec("SELECT bank_id, name FROM banks ORDER BY bank_id");

    std::vector<Bank> result;
    for (const auto& row : res)
    {
        result.push_back(Bank{row[0].as<std::string>(), row[1].as<std::string>()});
    }
    return result;
}

std::optional<Bank> BankRepository::get_by_id(const std::string& id)
{
    pqxx::work   txn(db_.connection());
    pqxx::result res = txn.exec_params("SELECT bank_id, name FROM banks WHERE bank_id = $1", id);
    if (res.empty())
        return std::nullopt;

    const auto& row = res[0];
    return Bank{row[0].as<std::string>(), row[1].as<std::string>()};
}

void BankRepository::insert(const Bank& b)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("INSERT INTO banks (bank_id, name) VALUES ($1, $2)", b.id, b.name);
    txn.commit();
}

void BankRepository::update(const std::string id, const Bank& b)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("UPDATE banks SET bank_id = $2, name = $1 WHERE bank_id = $3", b.name, b.id,
                    id);
    txn.commit();
}

void BankRepository::remove(const std::string& id)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("DELETE FROM banks WHERE bank_id = $1", id);
    txn.commit();
}
