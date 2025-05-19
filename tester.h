#ifndef TESTER_H
#define TESTER_H

#include <string>

std::string run_tests_in_docker(const std::string& user_code, const std::string& tests_dir);

#endif