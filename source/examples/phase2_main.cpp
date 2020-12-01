#include "./ECS/GameStateManager.h"
#include <application.hpp>

class anyClass : public our::Application{
public:
 our::Application* anyFn(){
   return this;
}
};


int main(int argc, char** argv) {
    GameStateManager* main_GSM=new GameStateManager();
    our::Application* ourApp=anyClass().anyFn();

    main_GSM->run(ourApp);
    return 0;
}