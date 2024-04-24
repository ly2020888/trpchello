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

#pragma once

#include "university.trpc.pb.h"

namespace University {
namespace StudentManagement {

namespace stu = trpc::university::stu;

class UniversityServiceImpl : public stu::University {
public:
  ::trpc::Status Ping(::trpc::ServerContextPtr context,
                      const ::trpc::university::stu::PingMessage *request,
                      ::trpc::university::stu::PingMessage *response) override;
  ::trpc::Status
  GetEnvelopment(::trpc::ServerContextPtr context,
                 const ::trpc::university::stu::Envelopment *request,
                 ::trpc::university::stu::Envelopment *response) override;
  ::trpc::Status
  PutEnvelopment(::trpc::ServerContextPtr context,
                 const ::trpc::university::stu::Envelopment *request,
                 ::trpc::university::stu::Envelopment *response) override;
};

} // namespace StudentManagement
} // namespace University
