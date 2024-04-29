//
// Created by 刘毅 on 2024/4/25.
//

#include "database.h"
#include "gflags/gflags.h"
#include "trpc/client/redis/cmdgen.h"
#include "trpc/client/redis/redis_service_proxy.h"
#include "trpc/common/runtime_manager.h"
#include "trpc/common/trpc_app.h"
namespace University {
namespace DB {

DEFINE_string(config, "trpc_cpp_fiber_server.yaml",
              "trpc cpp framework server_config file");

void Redis::ParseClientConfig(int argc, char *argv[]) {

  google::ParseCommandLineFlags(&argc, &argv, true);
  google::CommandLineFlagInfo info;
  if (GetCommandLineFlagInfo("config", &info) && info.is_default) {
    std::cerr << "start client with client_config, for example: " << argv[0]
              << " --client_config=/client/client_config/filepath" << std::endl;
    exit(-1);
  }
  std::cout << "FLAGS_client_config:" << FLAGS_config << std::endl;
  if (const int ret = ::trpc::TrpcConfig::GetInstance()->Init(FLAGS_config);
      ret != 0) {
    std::cerr << "load client_config failed." << std::endl;
    exit(-1);
  }
}

void Redis::connect() {
  if (trpc_clinet == nullptr) {
    trpc_clinet = ::trpc::GetTrpcClient();
  }
  auto proxy =
      trpc_clinet->GetProxy<trpc::redis::RedisServiceProxy>("redis_server");
  if (proxy != nullptr) {
    this->proxy = proxy;
    TRPC_FMT_INFO("Establishing a link with the redis service succeeded");
  } else {
    TRPC_FMT_ERROR("Failed to establish a link with redis");
    std::terminate();
  }
};

void Redis::set(const std::string &key, const std::string &value) {
  const trpc::ClientContextPtr ctx = trpc::MakeClientContext(proxy);
  trpc::redis::Reply reply;
  const auto status =
      proxy->Command(ctx, &reply, trpc::redis::cmdgen{}.set(key, value));
  if (!status.OK()) {
    TRPC_FMT_ERROR("redis set command fail, error msg:{}",
                   status.ErrorMessage());
  } else {
    TRPC_FMT_INFO("redis set command success, reply:{}", reply.GetString());
  }
}

void Redis::mset(
    const std::vector<std::pair<std::string, std::string>> &key_values) {
  const trpc::ClientContextPtr ctx = trpc::MakeClientContext(proxy);
  trpc::redis::Reply reply;
  const auto status =
      proxy->Command(ctx, &reply, trpc::redis::cmdgen{}.mset(key_values));
  if (!status.OK()) {
    TRPC_FMT_ERROR("redis mset command fail, error msg:{}",
                   status.ErrorMessage());
  } else {
    TRPC_FMT_INFO("redis mset command success, reply:{}", reply.GetString());
  }
}

std::vector<std::string> Redis::mget(const std::vector<std::string> keys) {
  const trpc::ClientContextPtr ctx = trpc::MakeClientContext(proxy);
  trpc::redis::Reply reply;
  const auto status =
      proxy->Command(ctx, &reply, trpc::redis::cmdgen{}.mget(keys));
  if (!status.OK()) {
    TRPC_FMT_ERROR("redis mget command fail, error msg:{}",
                   status.ErrorMessage());
    return {};
  }
  auto array = reply.GetArray();
  std::vector<std::string> result;
  for (auto &i : array) {
    result.push_back(i.GetString());
  }
  TRPC_FMT_INFO("redis mget command success, reply:{}", reply.GetString());
  return result;
}

std::string Redis::get(const std::string &key) {
  trpc::ClientContextPtr ctx = trpc::MakeClientContext(proxy);
  trpc::redis::Reply reply;
  auto status = proxy->Command(ctx, &reply, trpc::redis::cmdgen{}.get(key));
  if (!status.OK()) {
    // RPC get error,maybe timeout
    TRPC_FMT_ERROR("redis get command fail, error msg:{}",
                   status.ErrorMessage());
  } else {
    // Success
    TRPC_FMT_INFO("redis get command success, reply:{}", reply.GetString());
    return reply.GetString();
  }
  return "";
}

bool Redis::del(const std::vector<std::string> &keys) {
  trpc::ClientContextPtr ctx = trpc::MakeClientContext(proxy);
  trpc::redis::Reply reply;
  auto status = proxy->Command(ctx, &reply, trpc::redis::cmdgen{}.del(keys));
  if (!status.OK()) {
    // RPC get error,maybe timeout
    TRPC_FMT_ERROR("redis del command fail, error msg:{}",
                   status.ErrorMessage());
  } else {
    // Success
    TRPC_FMT_INFO("redis get command success, reply:{}", reply.GetString());
    return true;
  }
  return false;
}

void Redis::close() {}

} // namespace DB
}