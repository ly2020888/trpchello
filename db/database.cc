//
// Created by 刘毅 on 2024/4/25.
//

#include "database.h"
#include "trpc/client/redis/cmdgen.h"
#include "trpc/client/redis/redis_service_proxy.h"

#include "trpc/common/trpc_app.h"
namespace University {
namespace DB {
void Redis::connect() {

  auto proxy =
      ::trpc::GetTrpcClient()->GetProxy<trpc::redis::RedisServiceProxy>(
          "redis_server");
  if (proxy != nullptr) {
    this->proxy = proxy;
    TRPC_FMT_INFO("Establishing a link with the redis service succeeded");
  } else {
    TRPC_FMT_ERROR("Failed to establish a link with redis");
    // std::terminate();
  }
};

void Redis::set(const std::string &key, const std::string &value) {
  const trpc::ClientContextPtr ctx = trpc::MakeClientContext(this->proxy);
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

std::string Redis::get(const std::string &key) {
  trpc::ClientContextPtr ctx = trpc::MakeClientContext(proxy);
  trpc::redis::Reply reply;
  auto status = proxy->Command(ctx, &reply, trpc::redis::cmdgen{}.get(key));
  if (!status.OK()) {
    // RPC get error,maybe timeout
    std::cout << "Fiber call redis get command fail, error msg:"
              << status.ErrorMessage() << std::endl;
  } else if (reply.IsError()) {
    // Redis-Server return error
    std::cout << "Fiber call redis get command fail, error msg:"
              << reply.GetString() << std::endl;
  } else if (reply.IsNil()) {
    // Redis-Server return Nil if not exists this redis-key
    std::cout << "Fiber call redis get command return Nil" << std::endl;
  } else {
    // Success
    std::cout << "Fiber call redis get command success, reply:"
              << reply.GetString() << std::endl;
    return reply.GetString();
  }
  return "";
}

bool Redis::del(const std::string &key) {
  // TODO
  return false;
}

void Redis::close() {}

} // namespace DB
}