#ifndef FILEOP_H
#define FILEOP_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace Rendervis::Util {

    std::string LoadFileToString(const std::string& filename) {
        std::string result = "";

        std::string line = "";
        std::ifstream file(filename.c_str());

        if (file.is_open()) {
            while (std::getline(file, line)) {
                result += line + '\n';
            }
            file.close();
        } else {
            std::cerr << "ERROR::FILE LOADING::Failed to Open File" << errno << "\n";
        }
        return result;
    }

}  // namespace Rendervis::Util

#endif