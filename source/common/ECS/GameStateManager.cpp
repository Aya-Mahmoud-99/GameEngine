#include "GameStateManager.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD2
#include <imgui_impl/imgui_impl_glfw.h>
#include <imgui_impl/imgui_impl_opengl3.h>

using namespace std;
void GameStateManager::GoToState(GameState *PointerToGS) {
    CurrentGameState=NextGameState;
    NextGameState=PointerToGS;
}

    void GameStateManager::run(our::Application* app){



        glfwInit();
        app->configureOpenGL();                                      // This function sets OpenGL window hints.

        auto win_config = app->getWindowConfiguration();             // Returns the WindowConfiguration current struct instance.


        // Create a window with the given "WindowConfiguration" attributes.
        // If it should be fullscreen, monitor should point to one of the monitors (e.g. primary monitor), otherwise it should be null
        GLFWmonitor* monitor = win_config.isFullscreen ? glfwGetPrimaryMonitor() : nullptr;
        // The last parameter "share" can be used to share the resources (OpenGL objects) between multiple windows.
        app->window = glfwCreateWindow(win_config.size.x, win_config.size.y, win_config.title, monitor, nullptr);

        glfwMakeContextCurrent(app->window);         // Tell GLFW to make the context of our window the main context on the current thread.

        gladLoadGL(glfwGetProcAddress);         // Load the OpenGL functions from the driver


GameState* gamestatePointer=new GameState();
GameState* MenuStatePointer=new MenuState();
        GoToState(MenuStatePointer);

        app->setupCallbacks();
        app->keyboard.enable(app->window);
        app->mouse.enable(app->window);
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark();



        // Initialize ImGui for GLFW and OpenGL
        ImGui_ImplGlfw_InitForOpenGL(app->window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");

        double last_frame_time = glfwGetTime();
        while(!glfwWindowShouldClose(app->getWindow())) {
            glfwPollEvents(); // Read all the user events and call relevant callbacks.

            // Start a new ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            app->onImmediateGui(io); // Call to run any required Immediate GUI.
            app->keyboard.setEnabled(!io.WantCaptureKeyboard, app->window);
            app->mouse.setEnabled(!io.WantCaptureMouse, app->window);
            ImGui::Render();

            if (app->getKeyboard().isPressed(GLFW_KEY_H)) {
                cout << "XXXXXXXXXXXX   DDDDD IS PRESSED" << endl;
                GoToState(MenuStatePointer);
            } else if (app->getKeyboard().isPressed(GLFW_KEY_G) && CurrentGameState == MenuStatePointer) {
                cout << "XXXXXXXXXXXX   GGGGG IS PRESSED" << endl;
                GoToState(gamestatePointer);
            } else{


                auto frame_buffer_size = app->getFrameBufferSize();
            glViewport(0, 0, frame_buffer_size.x, frame_buffer_size.y);

            double current_frame_time = glfwGetTime();
            //CurrentGameState->onDraw(app,current_frame_time - last_frame_time);
            cout << "AAAAAAAAAAAAAAA  1" << endl;
            if (NextGameState != nullptr) {
                cout << "AAAAAAAAAAAAAAA  2" << endl;
                if (CurrentGameState != nullptr) {
                    cout << "AAAAAAAAAAAAAAA  3" << endl;
                    CurrentGameState->onExit(app);
                }
                cout << "AAAAAAAAAAAAAAA  4" << endl;
                CurrentGameState = NextGameState;
                NextGameState = nullptr;
                CurrentGameState->onEnter(app);
            }
            if (CurrentGameState != nullptr) {
                cout << "AAAAAAAAAAAAAAA  5" << endl;
                CurrentGameState->onDraw(app, current_frame_time - last_frame_time);

            }
            glfwSwapBuffers(app->window);

            app->keyboard.update();
            app->mouse.update();

//
            last_frame_time = current_frame_time;
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Render the ImGui to the framebuffer
            // If F12 is pressed, take a screenshot
            if (app->keyboard.justPressed(GLFW_KEY_F12)) {
                glViewport(0, 0, frame_buffer_size.x, frame_buffer_size.y);
                //std::stringstream stream;
                auto time = std::time(nullptr);
                auto localtime = std::localtime(&time);
            }
        }
        }
        if(CurrentGameState!= nullptr){
            cout << "AAAAAAAAAAAAAAA  6" <<endl;
            CurrentGameState->onExit(app);}


    }






