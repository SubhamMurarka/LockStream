#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../fileHandling/IO.hpp"

enum class Action {
    ENCRYPT,
    DECRYPT
};

struct Task {
    std::string filePath;
    std::fstream f_stream;
    Action action;

    Task(std::fstream&& stream, Action act, const std::string& filepath);
    std::string toString() const; 
    static Task fromString(const std::string& taskData);
};

#endif
