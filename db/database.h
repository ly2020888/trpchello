//
// Created by 刘毅 on 2024/4/25.
//

#pragma once
#include "trpc/client/redis/redis_service_proxy.h"
#include "trpc/common/trpc_app.h"

#include <string>
namespace University {
namespace DB {
class Database {
public:
  virtual ~Database(){};
  virtual void connect() = 0;
  virtual void set(const std::string &key, const std::string &value) = 0;
  virtual std::string get(const std::string &key) = 0;
  virtual bool del(const std::vector<std::string> &keys) = 0;
  virtual void
  mset(const std::vector<std::pair<std::string, std::string>> &key_values) = 0;
  virtual std::vector<std::string>
  mget(const std::vector<std::string> keys) = 0;
  virtual void close() = 0;
};

class Redis final : public Database {
public:
  void connect() override;
  void set(const std::string &key, const std::string &value) override;
  std::string get(const std::string &key) override;
  bool del(const std::vector<std::string> &keys) override;
  void mset(const std::vector<std::pair<std::string, std::string>> &key_values)
      override;
  std::vector<std::string> mget(const std::vector<std::string> keys) override;
  void close() override;
  void ParseClientConfig(int argc, char *argv[]);
  ~Redis() override {}
  Redis(int argc, char *argv[]) { ParseClientConfig(argc, argv); }

private:
  std::shared_ptr<trpc::redis::RedisServiceProxy> proxy;
  std::shared_ptr<trpc::TrpcClient> trpc_clinet;
};
} // namespace DB

} // namespace University
