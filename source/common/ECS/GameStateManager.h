#include "GameState.h"
#ifndef GameStateManager_H
#define GameStateManager_H
#include "MenuState.h"

class GameStateManager {
private:
    GameState* CurrentGameState= nullptr;            //pointer to the current game state
    GameState* NextGameState=nullptr;    //pointer to the next game state

public:

    void GoToState(GameState* PointerToGS);
    void run(our::Application* app);


};

#endif








