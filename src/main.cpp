
#include <memory>
#include <iostream>
#include "engine.h"
#include "utils.h"

int main() {

    auto engine = std::make_unique<Engine>();
    engine->loop();
}