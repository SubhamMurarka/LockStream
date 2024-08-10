#include "Task.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../fileHandling/IO.hpp"

Task::Task(std::fstream&& stream, Action act, const std::string& filepath) {
        f_stream = std::move(stream);
        action = act;
        filePath = filepath;
}

std::string Task::toString() const {
        std::ostringstream oss;
        oss << filePath << "," << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");
        return oss.str();
}

Task Task::fromString(const std::string& taskData) {
        std::istringstream iss(taskData);
        std::string filePath;
        std::string actionStr;

        if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr)) {
            Action action = (actionStr == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);
            IO io(filePath);
            std::fstream f_stream = std::move(io.getFileStream());
            if (f_stream.is_open()) {
                return Task(std::move(f_stream), action, filePath);
            } else {
                throw std::runtime_error("Failed to open file: " + filePath);
            }
        } else {
            throw std::runtime_error("Invalid task data format");
        }
}

