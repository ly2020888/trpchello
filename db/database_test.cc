//
// Created by 刘毅 on 2024/4/25.
//

#include <iostream>
#include <string>

#include "database.h"
#include "gflags/gflags.h"
#include "trpc/common/runtime_manager.h"
#include "gtest/gtest.h"

namespace University {
namespace DB {
int argc = 0;
char **argv = nullptr;
void Run(Database *db) {
  db->connect();
  auto result = db->get("Student505");
  TRPC_FMT_INFO("get {}", result);
}

namespace testing {

TEST(RedisServiceTest, RedisConnection) {
  Database *redis = new Redis(argc, argv);
  ::trpc::RunInTrpcRuntime([&]() {
    DB ::Run(redis);
    return 0;
  });
}

} // namespace testing
} // namespace DB
} // namespace University

int main(int argc, char **argv) {
  University::DB::argc = argc;
  University::DB::argv = argv;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}