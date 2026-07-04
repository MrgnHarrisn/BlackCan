add_rules("mode.debug", "mode.release")

set_languages("c++17")

add_requires("fmt")
add_requires("glfw 3.4")
add_requires("glad 0.1.36")
add_requires("imgui 1.92.7-docking", {configs= {glfw = true, opengl3 = true}})
add_requires("assimp 6.0.4")
add_requires("spdlog 1.17.0")
add_requires("stb 2026.03.18")
add_requires("nlohmann_json 3.12.0")
add_requires("glm 1.0.3")

target("BlackCan")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("include/")
    add_packages("fmt", "glfw", "glad",
                "imgui", "assimp", "spdlog",
                "stb", "nlohmann_json", "glm")