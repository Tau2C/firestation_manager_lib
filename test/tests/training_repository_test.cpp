#include <gtest/gtest.h>
#include "../lib/include/db_manager.hpp"
#include "../lib/include/training_repository.hpp"

#include "utils.hpp"

class TrainingRepositoryTest : public ::testing::Test {
protected:
    std::unique_ptr<DBManager> db;
    std::unique_ptr<TrainingRepository> repo;

    void SetUp() override {
        db = std::make_unique<DBManager>(get_connection_string());
        repo = std::make_unique<TrainingRepository>(*db);

        pqxx::work txn(db->connection());
        txn.exec("DELETE FROM firefighter_training;");
        txn.exec("DELETE FROM trainings;");
        txn.commit();
    }
};

TEST_F(TrainingRepositoryTest, InsertAndGetTraining) {
    Training t{.id = "FSafety", .name = "Fire Safety"};

    repo->insert(t);
    auto all = repo->get_all();

    ASSERT_FALSE(all.empty());
    EXPECT_EQ(all[0].name, "Fire Safety");
}

TEST_F(TrainingRepositoryTest, UpdateTraining) {
    Training t{.id = "FAid", .name = "First Aid"};
    repo->insert(t);

    auto inserted = repo->get_all()[0];
    inserted.name = "Advanced First Aid";
    repo->update(inserted);

    auto fetched = repo->get_by_id(inserted.id);
    ASSERT_TRUE(fetched.has_value());
    EXPECT_EQ(fetched->name, "Advanced First Aid");
}

TEST_F(TrainingRepositoryTest, RemoveTraining) {
    Training t{.id = "TTraining", .name = "Test Training"};
    repo->insert(t);

    auto inserted = repo->get_all()[0];
    repo->remove(inserted.id);

    auto fetched = repo->get_by_id(inserted.id);
    EXPECT_FALSE(fetched.has_value());
}
