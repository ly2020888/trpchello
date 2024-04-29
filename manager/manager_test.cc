//
// Created by 刘毅 on 2024/4/28.
//
#include "manager.h"
#include "student.pb.h"
#include "gtest/gtest.h"
#include <random>

namespace University {
namespace testing {

namespace stu = trpc::university::stu;
constexpr int student_numbers = 10;

static stu::Student createRandomStudent() {
  const auto name = "Student" + std::to_string(rand() % 1000); // 随机姓名
  const auto birthYear = 1990 + rand() % 20;                   // 随机年份
  const auto age = 16 + rand() % 10;                           // 随机年龄
  const auto gender = (rand() % 2 == 0) ? "male" : "female";   // 随机性别
  const auto score =
      static_cast<float>(rand() % 101) / 10.0f; // 随机分数，范围在0到10之间
  return Manager::create_student(name, birthYear, age, gender, score);
}

int argc = 0;
char **argv = nullptr;
TEST(ManagerTest, ManagerStoreStudent) {
  std::vector<stu::Student> array;
  std::vector<std::string> uuids;

  auto m = Manager(argc, argv);
  array.reserve(student_numbers * 2);
  for (int i = 0; i < student_numbers; ++i) {
    auto student = createRandomStudent();
    uuids.push_back(student.name());
    array.push_back(student);
  }
  m.store_students(array);

  for (const auto &i : array) {
    Manager::display(i);
  }
  TRPC_FMT_INFO("======测试取数据=====");
  auto temp = m.get_students(uuids);
  for (auto &i : temp) {
    Manager::display(i);
  }
}
} // namespace testing
} // namespace University

int main(int argc, char **argv) {
  University::testing::argc = argc;
  University::testing::argv = argv;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}