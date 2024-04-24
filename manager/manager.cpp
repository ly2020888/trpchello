//
// Created by 刘毅 on 2024/4/24.
//

#include "manager.h"

namespace University {

void display(const trpc::university::stu::Student &student) {
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
}