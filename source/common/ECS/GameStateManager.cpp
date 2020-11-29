#include "GameStateManager.h"


void GameStateManager::GoToState(GameState *PointerToGS) {
    NextGameState=PointerToGS;
}

    void GameStateManager::run(our::Application* app,World* WorldPointer,double deltaTime){
//GoToState(defaultstate);
        while(!glfwWindowShouldClose(app->getWindow())){
            if(NextGameState!= nullptr){
                if(CurrentGameState!= nullptr){
                    CurrentGameState->onExit(app,WorldPointer);
                }
                CurrentGameState=NextGameState;
                NextGameState= nullptr;
                CurrentGameState->onEnter(app,WorldPointer);
            }
            if(CurrentGameState!= nullptr){
                CurrentGameState->onDraw(app,WorldPointer,deltaTime);

            }
        }
        if(CurrentGameState!= nullptr){CurrentGameState->onExit(app,WorldPointer);}

    }






