#include "GameState.cpp"
#ifndef GameStateManager_H
#define GameStateManager_H

class GameStateManager {
private:
    GameState* CurrentGameState= nullptr;            //pointer to the current game state
    GameState* NextGameState=nullptr;    //pointer to the next game state

public:
    void GoToState(GameState* PointerToGS);
    void run(our::Application* app,World* WorldPointer,double deltaTime);


};

#endif








