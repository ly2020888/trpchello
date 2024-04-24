//
//
// Tencent is pleased to support the open source community by making tRPC
// available.
//
// Copyright (C) 2023 THL A29 Limited, a Tencent company.
// All rights reserved.
//
// If you have downloaded a copy of the tRPC source code from Tencent,
// please note that tRPC source code is licensed under the  Apache 2.0 License,
// A copy of the Apache 2.0 License is included in this file.
//
//

#include "fmt/format.h"
#include <iostream>
#include <memory>
#include <string>

#include "trpc/common/trpc_app.h"

#include "manager/manager.h"
#include "manager/student.pb.h"
#include "university_service.h"
namespace University {

namespace StudentManagement {

class UniversityServer : public ::trpc::TrpcApp {
public:
  int Initialize() override {
    const auto &config = ::trpc::TrpcConfig::GetInstance()->GetServerConfig();
    // Set the service name, which must be the same as the value of the
    // `/server/service/name` configuration item in the configuration file,
    // otherwise the framework cannot receive requests normally.
    std::string service_name =
        fmt::format("{}.{}.{}.{}", "trpc", config.app, config.server, "stu");
    TRPC_FMT_INFO("service name:{}", service_name);

    RegisterService(service_name, std::make_shared<UniversityServiceImpl>());

    return 0;
  }

  void Destroy() override {}
};

} // namespace StudentManagement
} // namespace University

int main(int argc, char **argv) {

  University::StudentManagement::UniversityServer server;
  trpc::university::stu::Student s =
      University::Manager::createStudent("haha", 11, 1, "man", 1.9);
  auto bytes = University::Manager::serialize(s);
  for (const auto i : bytes) {
    std::cout << static_cast<int>(i) << " ";
  }
  std::cout << "\n";

  auto stuu = University::Manager::deserialize(bytes);
  University::display(stuu);
  server.Main(argc, argv);
  server.Wait();

  return 0;
}