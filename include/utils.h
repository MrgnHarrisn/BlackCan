#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <fmt/core.h>
#include <fmt/color.h>

using namespace std;

namespace Utils
{
    static string readFileToString(const string &filepath)
    {
        ifstream file(filepath);
        if (!file.is_open())
        {
            fmt::println("Error opening");
            return "";
        }
        ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    static void errorMessage(const string& where, const string& why) {
        fmt::println(fmt::fg(fmt::color::red), where);
        fmt::println(fmt::fg(fmt::color::coral), why);
    }

}