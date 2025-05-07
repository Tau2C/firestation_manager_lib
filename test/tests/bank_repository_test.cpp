#include <gtest/gtest.h>

#include "../lib/include/db_manager.hpp"
#include "../lib/include/bank_repository.hpp"

#include "utils.hpp"

class BankRepositoryTest : public ::testing::Test {
protected:
    std::unique_ptr<DBManager> db;
    std::unique_ptr<BankRepository> repo;

    void SetUp() override {
        db = std::make_unique<DBManager>(get_connection_string());
        repo = std::make_unique<BankRepository>(*db);

        pqxx::work txn(db->connection());
        txn.exec("DELETE FROM banks");
        txn.commit();
    }
};

TEST_F(BankRepositoryTest, InsertAndGetBank) {
    Bank b{"1234", "Galactic Bank"};
    repo->insert(b);

    auto result = repo->get_by_id("1234");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->id, "1234");
    EXPECT_EQ(result->name, "Galactic Bank");
}

TEST_F(BankRepositoryTest, UpdateBank) {
    repo->insert({"4321", "Bank A"});
    repo->update("4321", {"4321", "Bank B"});

    auto b = repo->get_by_id("4321");
    ASSERT_TRUE(b.has_value());
    EXPECT_EQ(b->name, "Bank B");
}

TEST_F(BankRepositoryTest, DeleteBank) {
    repo->insert({"1111", "Delete Me"});
    repo->remove("1111");

    auto b = repo->get_by_id("1111");
    EXPECT_FALSE(b.has_value());
}
