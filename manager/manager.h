//
// Created by 刘毅 on 2024/4/24.
//

#pragma once
#include "db/database.h"
#include "student.pb.h"
#include "trpc/common/trpc_app.h"

#include <vector>
namespace stu = trpc::university::stu;
namespace University {

// db::obj
class Manager {
public:
  static stu::Student create_student(const std::string &name, int id, int age,
                                     const std::string &gender, float score) {
    stu::Student student;
    student.set_name(name);
    student.set_id(id);
    student.set_age(age);
    student.set_gender(gender);
    student.set_score(score);
    return student;
  }

  static std::string serialize(const stu::Student &student) {
    std::string serialized_data;
    if (student.SerializeToString(&serialized_data)) {
      return serialized_data;
    }
    return {};
  }
  static stu::Student deserialize(const std::string &bytes) {
    stu::Student student;
    if (!student.ParseFromArray(bytes.data(), static_cast<int>(bytes.size()))) {
      TRPC_FMT_ERROR("Deserialization failed.");
      return {};
    }
    return student;
  }
  static void display(const trpc::university::stu::Student &student);
  void store_students(const std::vector<stu::Student> &stus);
  void store_student(const stu::Student &stu);
  stu::Student get_student(const std::string &uuid) const;
  std::vector<stu::Student>
  get_students(const std::vector<std::string> &uuids) const;
  Manager(int argc, char *argv[]) {
    db = std::make_unique<DB::Redis>(argc, argv);
  }

private:
  std::unique_ptr<DB::Database> db;
};

} // namespace University

