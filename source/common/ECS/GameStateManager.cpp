#include "GameStateManager.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD2
#include <imgui_impl/imgui_impl_glfw.h>
#include <imgui_impl/imgui_impl_opengl3.h>


void GameStateManager::GoToState(GameState *PointerToGS) {
    CurrentGameState=NextGameState;
    NextGameState=PointerToGS;
}

    void GameStateManager::run(our::Application* app){
//GoToState(defaultstate);
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
CurrentGameState=gamestatePointer;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark();

        // Initialize ImGui for GLFW and OpenGL
        ImGui_ImplGlfw_InitForOpenGL(app->window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");

CurrentGameState->onEnter(app);
        double last_frame_time = glfwGetTime();
        while(!glfwWindowShouldClose(app->getWindow())){
            glfwPollEvents(); // Read all the user events and call relevant callbacks.

            // Start a new ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            app->onImmediateGui(io); // Call to run any required Immediate GUI.

            // If ImGui is using the mouse or keyboard, then we don't want the captured events to affect our keyboard and mouse objects.
            // For example, if you're focusing on an input and writing "W", the keyboard object shouldn't record this event.
//            keyboard.setEnabled(!io.WantCaptureKeyboard, window);
//            mouse.setEnabled(!io.WantCaptureMouse, window);

            // Render the ImGui commands we called (this doesn't actually draw to the screen yet.
            ImGui::Render();


            auto frame_buffer_size = app->getFrameBufferSize();
            glViewport(0, 0, frame_buffer_size.x, frame_buffer_size.y);

            double current_frame_time = glfwGetTime();
           // CurrentGameState->onDraw(app,current_frame_time - last_frame_time);
            last_frame_time=current_frame_time;


            glfwSwapBuffers(app->window);
        }
        CurrentGameState->onExit(app);
            /*if(NextGameState!= nullptr){
                if(CurrentGameState!= nullptr){
                    CurrentGameState->onExit(app);
                }
                CurrentGameState=NextGameState;
                NextGameState= nullptr;
                CurrentGameState->onEnter(app);
            }
            if(CurrentGameState!= nullptr){
                CurrentGameState->onDraw(app,deltaTime);

            }
        }
        if(CurrentGameState!= nullptr){CurrentGameState->onExit(app);}*/

    }






