// Settings.h
#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>   // C++17 for directory creation

class Settings
{
public:
    // Delete copy/move constructors and assignment operators
    Settings(const Settings &) = delete;
    Settings &operator=(const Settings &) = delete;
    Settings(Settings &&) = delete;
    Settings &operator=(Settings &&) = delete;

    // Global access point (Meyers Singleton – thread‑safe since C++11)
    static Settings &getInstance()
    {
        static Settings instance;
        return instance;
    }

    // --- Window specific getters ---
    int getWindowWidth() const { return value("window.width", 800); }
    int getWindowHeight() const { return value("window.height", 600); }
    std::string getWindowTitle() const { return value("window.title", std::string("My Game")); }

    // --- Additional window settings (optional) ---
    bool isWindowResizable() const { return value("window.resizable", false); }
    bool isWindowFullscreen() const { return value("window.fullscreen", false); }
    int getWindowMaxFPS() const { return value("window.maxFPS", 60); }

    // --- Generic access for any other key (with default) ---
    template <typename T>
    T value(const std::string &key, const T &default_value = T{}) const
    {
        size_t start = 0;
        size_t end = key.find('.');
        nlohmann::json current = data_;

        while (end != std::string::npos)
        {
            std::string part = key.substr(start, end - start);
            if (!current.is_object() || !current.contains(part))
                return default_value;
            current = current[part];
            start = end + 1;
            end = key.find('.', start);
        }

        std::string last = key.substr(start);
        if (!current.is_object() || !current.contains(last))
            return default_value;

        try
        {
            return current[last].get<T>();
        }
        catch (...)
        {
            return default_value;
        }
    }

    // Reload the settings file at runtime
    void reload()
    {
        loadFromFile(getSettingsPath());
    }

private:
    nlohmann::json data_;

    Settings()
    {
        // Ensure the settings folder exists
        std::filesystem::create_directories("settings");

        const std::string path = getSettingsPath();

        // If the file does not exist, create it with default settings
        if (!std::filesystem::exists(path))
        {
            createDefaultSettingsFile(path);
        }

        loadFromFile(path);
    }

    ~Settings() = default;

    static std::string getSettingsPath()
    {
        return "settings/settings.json";
    }

    void loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Warning: Could not open " << filename
                      << ". Using default settings.\n";
            data_ = nlohmann::json::object();
            return;
        }

        try
        {
            file >> data_;
        }
        catch (const nlohmann::json::parse_error &e)
        {
            std::cerr << "JSON parse error in " << filename << ": " << e.what() << '\n';
            data_ = nlohmann::json::object();
        }
    }

    // Creates a JSON file with the default settings that match the getters
    void createDefaultSettingsFile(const std::string &filename) const
    {
        nlohmann::json default_json = {
            {"window", {
                {"width", 800},
                {"height", 800},
                {"title", "My Game"},
                {"resizable", false},
                {"fullscreen", false},
                {"maxFPS", 60}
            }}
        };

        std::ofstream file(filename);
        if (file.is_open())
        {
            file << default_json.dump(4);   // pretty print with 4 spaces
            std::cout << "Created default settings file: " << filename << "\n";
        }
        else
        {
            std::cerr << "Error: Could not create settings file " << filename << "\n";
        }
    }
};