//
// Created by 刘毅 on 2024/4/25.
//

#include <iostream>
#include <string>

#include "database.h"
#include "gflags/gflags.h"
#include "trpc/client/redis/cmdgen.h"
#include "trpc/common/runtime_manager.h"
#include "gtest/gtest.h"

DEFINE_string(config, "trpc_cpp_fiber_server.yaml",
              "trpc cpp framework server_config file");

namespace University {
namespace DB {

void Run() {
  Database *redis = new Redis();
  redis->connect();
  GTEST_LOG_(INFO) << "Connection to Redis established.";
  redis->set("A", "a");
  redis->get("A");
}
void ParseClientConfig(int argc, char *argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::CommandLineFlagInfo info;
  if (GetCommandLineFlagInfo("config", &info) && info.is_default) {
    std::cerr << "start client with client_config, for example: " << argv[0]
              << " --client_config=/client/client_config/filepath" << std::endl;
    exit(-1);
  }

  std::cout << "FLAGS_client_config:" << FLAGS_config << std::endl;

  int ret = ::trpc::TrpcConfig::GetInstance()->Init(FLAGS_config);
  if (ret != 0) {
    std::cerr << "load client_config failed." << std::endl;
    exit(-1);
  }
}
namespace testing {

TEST(RedisServiceTest, RedisConnection) {
  ::trpc::RunInTrpcRuntime([]() {
    DB ::Run();
    return 0;
  });
}

} // namespace testing
} // namespace DB
} // namespace University

int main(int argc, char **argv) {
  University::DB::ParseClientConfig(argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}