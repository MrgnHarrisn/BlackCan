#include "engine.h"
#include <memory>

int main()
{
	auto engine = std::make_unique<Engine>();
	engine->loop();
}