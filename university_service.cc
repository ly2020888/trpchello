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

#include "university_service.h"

#include <string>

#include "trpc/common/status.h"
#include "trpc/log/trpc_log.h"

namespace University {
namespace StudentManagement {
namespace stu = ::trpc::university::stu;

::trpc::Status
UniversityServiceImpl::Ping(::trpc::ServerContextPtr context,
                            const ::trpc::university::stu::PingMessage *request,
                            ::trpc::university::stu::PingMessage *response) {
  TRPC_FMT_INFO("Ping from remote address: {}:{}.", context->GetIp(),
                context->GetPort());
  const std::string res = "pong";
  response->set_ping(res);
  return ::trpc::kSuccStatus;
}

::trpc::Status UniversityServiceImpl::GetEnvelopment(
    ::trpc::ServerContextPtr context,
    const ::trpc::university::stu::Envelopment *request,
    ::trpc::university::stu::Envelopment *response) {
  // TODO
  return ::trpc::kSuccStatus;
}

::trpc::Status UniversityServiceImpl::PutEnvelopment(
    ::trpc::ServerContextPtr context,
    const ::trpc::university::stu::Envelopment *request,
    ::trpc::university::stu::Envelopment *response) {
  // TODO
  return ::trpc::kSuccStatus;
}
} // namespace StudentManagement
} // namespace University
