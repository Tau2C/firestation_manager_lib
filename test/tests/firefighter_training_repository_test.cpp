#include <gtest/gtest.h>
#include <string>
#include "../lib/include/db_manager.hpp"
#include "../lib/include/firefighter_training_repository.hpp"
#include "../lib/include/firefighter_repository.hpp"
#include "../lib/include/training_repository.hpp"

#include "utils.hpp"

class FirefighterTrainingRepositoryTest : public ::testing::Test
{
protected:
    std::unique_ptr<DBManager> db;
    std::unique_ptr<FirefighterTrainingRepository> repo;

    int firefighter_id;
    std::string training_id;

    void SetUp() override
    {
        db = std::make_unique<DBManager>(get_connection_string());
        repo = std::make_unique<FirefighterTrainingRepository>(*db);

        FirefighterRepository ff_repo{*db};
        TrainingRepository t_repo{*db};

        ff_repo.insert(Firefighter{
            .name = "Anna",
            .surname = "Nowak",
            .address = "",
            .pesel = "01234567890",
            .phone = "123456789",
            .account_number = "00109022000000000000000000"});

        firefighter_id = ff_repo.get_all().front().firefighter_id;

        t_repo.insert(
            {.id = "R_OPS",
             .name = "Rescue Ops"});
        training_id = t_repo.get_all().front().id;
    }
};

TEST_F(FirefighterTrainingRepositoryTest, InsertAndGet)
{
    FirefighterTraining tr{
        .id = 0,
        .firefighter_id = firefighter_id,
        .training_id = training_id,
        .date = std::chrono::system_clock::now(),
        .expiration = std::chrono::system_clock::now() + std::chrono::hours(24 * 365),
        .status = TrainingStatus::Valid};

    repo->insert(tr);
    auto all = repo->get_all();
    ASSERT_FALSE(all.empty());
    EXPECT_EQ(all[0].firefighter_id, firefighter_id);
}
