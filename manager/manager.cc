//
// Created by 刘毅 on 2024/4/24.
//

#include "manager.h"
#include "trpc/common/runtime_manager.h"

namespace University {

void Manager::display(const stu::Student &student) {
  // 定义格式化字符串
  std::string format_string =
      "Name: {}, ID: {}, Age: {}, Gender: {}, Score: {}";

  // 使用 fmt::format 函数将学生对象格式化为字符串
  std::string formatted_string =
      fmt::format(format_string, student.name(), student.id(), student.age(),
                  student.gender(), student.score());

  // 打印格式化后的字符串
  std::cout << formatted_string << std::endl;
}
// FIXME:存数据之后立刻读为空，需要等待极短的时间。
void Manager::store_students(const std::vector<stu::Student> &stus) {
  trpc::RunInTrpcRuntime([&]() -> int {
    this->db->connect();
    std::vector<std::pair<std::string, std::string>> temp;
    for (auto &i : stus) {
      auto student_bytes = Manager::serialize(i);
      temp.push_back(std::make_pair(i.name(), student_bytes));
    }
    this->db->mset(temp);
    return 0;
  });
}
void Manager::store_student(const stu::Student &stu) {}

stu::Student Manager::get_student(const std::string &uuid) const {
  std::string student_bytes;
  trpc::RunInTrpcRuntime([&]() -> int {
    this->db->connect();
    student_bytes = db->get(uuid);
    return 0;
  });
  return Manager::deserialize(student_bytes);
}

std::vector<stu::Student>
Manager::get_students(const std::vector<std::string> &uuids) const {
  std::vector<stu::Student> students;
  students.reserve(uuids.size());
  trpc::RunInTrpcRuntime([&]() -> int {
    this->db->connect();
    auto student_byte = db->mget(uuids);
    for (auto &i : student_byte) {
      students.push_back(Manager::deserialize(i));
    }
    return 0;
  });
  return students;
}
}