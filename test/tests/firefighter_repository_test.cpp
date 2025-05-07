#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>
#include <optional>

#include "../lib/include/db_manager.hpp"
#include "../lib/include/firefighter_repository.hpp"

#include "utils.hpp"

class FirefighterRepositoryTest : public ::testing::Test {
protected:
    std::unique_ptr<DBManager> db;
    std::unique_ptr<FirefighterRepository> repo;

    void SetUp() override {
        db = std::make_unique<DBManager>(get_connection_string());
        repo = std::make_unique<FirefighterRepository>(*db);

        pqxx::work txn(db->connection());
        txn.exec("DELETE FROM firefighter_training;");
        txn.exec("DELETE FROM medical_examinations");
        txn.exec("DELETE FROM firefighters");
        txn.commit();
    }
};

TEST_F(FirefighterRepositoryTest, InsertAndGetFirefighter) {
    Firefighter f {
        .name = "Jan",
        .surname = "Kowalski",
        .address = "Main Street 12",
        .pesel = "03323101335",
        .phone = "728448450",
        .account_number = "00109022000000000000000000",
        .email = "example@email.com"
    };

    repo->insert(f);

    // Now fetch all and confirm it's the same
    auto all = repo->get_all();
    ASSERT_EQ(all.size(), 1);

    const Firefighter& fetched = all[0];
    EXPECT_EQ(fetched.name, "Jan");
    EXPECT_EQ(fetched.surname, "Kowalski");
    EXPECT_EQ(fetched.pesel, "03323101335");
}

TEST_F(FirefighterRepositoryTest, UpdateFirefighter) {
    Firefighter f {
        .name = "Anna",
        .surname = "Nowak",
        .address = "Sunset Blvd 1",
        .pesel = "98765432109",
        .phone = "987654321098",
        .account_number = "00209022000000000000000000",
        .email = "example@email.com"
    };

    repo->insert(f);
    auto all = repo->get_all();
    ASSERT_EQ(all.size(), 1);

    Firefighter& inserted = all[0];
    inserted.address = "Changed Address";
    repo->update(inserted.firefighter_id, inserted);

    auto updated = repo->get_by_id(inserted.firefighter_id);
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ(updated->address, "Changed Address");
}

TEST_F(FirefighterRepositoryTest, DeleteFirefighter) {
    Firefighter f {
        .name = "Marek",
        .surname = "Wójcik",
        .address = "Unknown",
        .pesel = "11122233344",
        .phone = "000111222333",
        .account_number = "00309022000000000000000000",
        .email = "example@email.com"
    };

    repo->insert(f);
    auto all = repo->get_all();
    ASSERT_EQ(all.size(), 1);

    repo->remove(all[0].firefighter_id);

    auto after = repo->get_all();
    EXPECT_TRUE(after.empty());
}
