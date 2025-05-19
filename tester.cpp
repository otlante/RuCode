#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <chrono>
#include <sstream>
#include "tester.h"

std::string run_tests_in_docker(const std::string& user_code, const std::string& tests_dir) {
    const std::string image_name = "cpp-code-tester";
    const std::string docker_dir = "docker";

    std::string temp_dir = "temp_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    std::filesystem::create_directory(temp_dir);
    std::filesystem::copy(tests_dir, temp_dir + "/tests", std::filesystem::copy_options::recursive);
    std::filesystem::copy(docker_dir + "/run.sh", temp_dir + "/run.sh", std::filesystem::copy_options::overwrite_existing);

    std::ofstream code_file(temp_dir + "/user_code.cpp");
    code_file << user_code;
    code_file.close();

    std::string cmd = "docker run --rm -v " + std::filesystem::absolute(temp_dir).string() +
                      ":/app " + image_name + " /bin/bash /app/run.sh > " + temp_dir + "/result.log 2>&1";
    system(cmd.c_str());

    std::ifstream result_file(temp_dir + "/result.log");
    std::ostringstream result_stream;
    result_stream << result_file.rdbuf();
    result_file.close();

    std::filesystem::remove_all(temp_dir);
    return result_stream.str();
}