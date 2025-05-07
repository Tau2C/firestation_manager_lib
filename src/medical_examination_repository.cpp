#include "medical_examination_repository.hpp"
#include "examination_type.hpp"
#include "utils.hpp"
#include <pqxx/pqxx>

MedicalExaminationRepository::MedicalExaminationRepository(DBManager& db) : db_(db)
{
}

std::vector<MedicalExamination> MedicalExaminationRepository::get_all()
{
    pqxx::work txn(db_.connection());
    auto       res = txn.exec("SELECT examination_id, examination_type, firefighter_id, date, "
                                    "expiration FROM medical_examinations");

    std::vector<MedicalExamination> result;
    for (const auto& row : res)
    {
        result.push_back(MedicalExamination{
            row[0].as<int>(), to_examination_type(row[1].as<std::string>()), row[2].as<int>(),
            from_pg_date(row[3].as<std::string>()), from_pg_date(row[4].as<std::string>())});
    }
    return result;
}

std::optional<MedicalExamination> MedicalExaminationRepository::get_by_id(int id)
{
    pqxx::work txn(db_.connection());
    auto res = txn.exec_params("SELECT * FROM medical_examinations WHERE examination_id = $1", id);
    if (res.empty())
        return std::nullopt;

    const auto& row = res[0];
    return MedicalExamination{row[0].as<int>(), to_examination_type(row[1].as<std::string>()),
                              row[2].as<int>(), from_pg_date(row[3].as<std::string>()),
                              from_pg_date(row[4].as<std::string>())};
}

void MedicalExaminationRepository::insert(const MedicalExamination& e)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("INSERT INTO medical_examinations (examination_type, "
                    "firefighter_id, date, expiration) VALUES ($1, $2, $3, $4)",
                    to_string(e.type), e.firefighter_id, to_pg_date(e.date),
                    to_pg_date(e.expiration));
    txn.commit();
}

void MedicalExaminationRepository::update(const int id, const MedicalExamination& e)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("UPDATE medical_examinations SET examination_id = $5, examination_type = $1, "
                    "firefighter_id = "
                    "$2, date = $3, expiration = $4 WHERE examination_id = $6",
                    to_string(e.type), e.firefighter_id, to_pg_date(e.date),
                    to_pg_date(e.expiration), e.id, id);
    txn.commit();
}

void MedicalExaminationRepository::remove(int id)
{
    pqxx::work txn(db_.connection());
    txn.exec_params("DELETE FROM medical_examinations WHERE examination_id = $1", id);
    txn.commit();
}
