//
// Created by 刘毅 on 2024/4/24.
//

#pragma once
#include "student.pb.h"
#include "trpc/common/trpc_app.h"

#include <vector>
namespace stu = trpc::university::stu;
// namespace trpc::university::stu
namespace University {

class Manager {
public:
  static stu::Student createStudent(const std::string &name, int id, int age,
                                    const std::string &gender, float score) {
    stu::Student student;
    student.set_name(name);
    student.set_id(id);
    student.set_age(age);
    student.set_gender(gender);
    student.set_score(score);
    return student;
  }
  static std::vector<char>
  serialize(const trpc::university::stu::Student &student) {
    std::string serialized_data;
    if (student.SerializeToString(&serialized_data)) {
      std::vector<char> bytes(serialized_data.begin(), serialized_data.end());
      return bytes;
    } else {
      return {};
    }
  }
  static trpc::university::stu::Student
  deserialize(const std::vector<char> &bytes) {
    trpc::university::stu::Student student;
    if (!student.ParseFromArray(bytes.data(), static_cast<int>(bytes.size()))) {
      TRPC_FMT_ERROR("Deserialization failed.");
    }
    return student;
  }
};

void display(const trpc::university::stu::Student &student);
} // namespace University

