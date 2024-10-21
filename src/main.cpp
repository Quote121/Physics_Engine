#include "gameEngine.hpp"

int main(int argv, char* args[])
{
    Log::Open();
    GameEngine engineInstance;
    engineInstance.Init();
    engineInstance.GameLoop();

    Log::Close();
    return 0;
}
