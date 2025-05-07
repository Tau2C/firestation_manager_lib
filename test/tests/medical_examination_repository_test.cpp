#include <gtest/gtest.h>

#include "../lib/include/db_manager.hpp"
#include "../lib/include/medical_examination_repository.hpp"
#include "../lib/include/firefighter_repository.hpp"
#include "../lib/include/utils.hpp"

#include "utils.hpp"

class MedicalExaminationRepositoryTest : public ::testing::Test {
protected:
    std::unique_ptr<DBManager> db;
    std::unique_ptr<MedicalExaminationRepository> repo;

    void SetUp() override {
        db = std::make_unique<DBManager>(get_connection_string());
        repo = std::make_unique<MedicalExaminationRepository>(*db);

        pqxx::work txn(db->connection());
        txn.exec("DELETE FROM medical_examinations");
        txn.exec("DELETE FROM firefighter_training");
        txn.exec("DELETE FROM trainings");
        txn.exec("DELETE FROM firefighters");
        txn.exec("INSERT INTO firefighters VALUES (1, 'Damian', 'Pietryka', 'Rzeszów ul. Lenartowicza 16/6', '03323101335', '+48728448450', '53124045354646523542164684');");
        txn.commit();
    }
};

TEST_F(MedicalExaminationRepositoryTest, InsertAndGet) {
    MedicalExamination e{
        0, ExaminationType::FIREFIGHTER, 1,
        from_pg_date("2025-01-01"), from_pg_date("2026-01-01")
    };
    repo->insert(e);

    auto all = repo->get_all();
    ASSERT_EQ(all.size(), 1);
    EXPECT_EQ(all[0].type, ExaminationType::FIREFIGHTER);
    EXPECT_EQ(all[0].firefighter_id, 1);
}

TEST_F(MedicalExaminationRepositoryTest, UpdateExam) {
    repo->insert({0, ExaminationType::FIREFIGHTER, 1, from_pg_date("2024-01-01"), from_pg_date("2025-01-01")});
    auto e = repo->get_all().at(0);
    e.expiration = from_pg_date("2026-06-06");
    repo->update(e.id, e);

    auto updated = repo->get_by_id(e.id);
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ(updated->expiration, from_pg_date("2026-06-06"));
}

TEST_F(MedicalExaminationRepositoryTest, DeleteExam) {
    repo->insert({0, ExaminationType::FIREFIGHTER, 1, from_pg_date("2023-01-01"), from_pg_date("2024-01-01")});
    auto e = repo->get_all().at(0);
    repo->remove(e.id);

    auto deleted = repo->get_by_id(e.id);
    EXPECT_FALSE(deleted.has_value());
}
