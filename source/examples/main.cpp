#include <application.hpp>
#include <shader.hpp>



class UniformsApplication : public our::Application {

    our::ShaderProgram program;
    GLuint vertex_array = 0;

    glm::vec2 scale = glm::vec2(1,1);
    glm::vec2 translation = glm::vec2(0,0);
    glm::vec3 color = glm::vec3(1, 0, 0);
    bool vibrate = false, flicker = false;
    bool shape[4]={false,false,false,false};

    our::WindowConfiguration getWindowConfiguration() override {
        return { "Uniforms", {1280, 720}, false };
    }

    void onInitialize() override {
        program.create();

        // smile face

        //if(shape[1]) {
           // program.attach("assets/shaders/SmileFace/Smile.vert", GL_VERTEX_SHADER);
           // program.attach("assets/shaders/SmileFace/Smile.frag", GL_FRAGMENT_SHADER);
        //}
        // heart
        //if(shape[1]) {
            //program.attach("assets/shaders/Heart/FullScreen.vert", GL_VERTEX_SHADER);
            //program.attach("assets/shaders/Heart/Heart.frag", GL_FRAGMENT_SHADER);
        //}



        // face3
       // if(shape[2]) {
          program.attach("assets/shaders/Heart/FullScreen.vert", GL_VERTEX_SHADER);
          program.attach("assets/shaders/Face/face3.frag", GL_FRAGMENT_SHADER);
       // }
        program.link();

        glGenVertexArrays(1, &vertex_array);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void onDraw(double deltaTime) override {
        //get mouse position and normalize it
        auto mouse_window_space = mouse.getMousePosition();
        mouse_window_space.y = ((getFrameBufferSize().y/2)-mouse_window_space.y)/(getFrameBufferSize().y/2);
        mouse_window_space.x = (mouse_window_space.x-(getFrameBufferSize().x/2))/(getFrameBufferSize().x/2);

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);

        GLuint scale_uniform_location = glGetUniformLocation(program, "scale");
        glUniform2f(scale_uniform_location, scale.x, scale.y);
        GLuint translation_uniform_location = glGetUniformLocation(program, "translation");
        glUniform2f(translation_uniform_location, mouse_window_space.x, mouse_window_space.y);
        GLuint color_uniform_location = glGetUniformLocation(program, "color");
        glUniform3f(color_uniform_location, color.r, color.g, color.b);

        GLuint time_uniform_location = glGetUniformLocation(program, "time");
        glUniform1f(time_uniform_location, glfwGetTime());
        GLuint vibrate_uniform_location = glGetUniformLocation(program, "vibrate");
        glUniform1i(vibrate_uniform_location, vibrate);
        GLuint flicker_uniform_location = glGetUniformLocation(program, "flicker");
        glUniform1i(flicker_uniform_location, flicker);
        GLuint shape1_radio_button = glGetUniformLocation(program, "Shape1");
        glUniform1i(shape1_radio_button,shape[0]);
        GLuint shape2_radio_button = glGetUniformLocation(program, "Shape2");
        glUniform1i(shape1_radio_button,shape[1]);
        GLuint shape3_radio_button = glGetUniformLocation(program, "Shape3");
        glUniform1i(shape1_radio_button,shape[2]);
        GLuint shape4_radio_button = glGetUniformLocation(program, "Shape4");
        glUniform1i(shape1_radio_button,shape[3]);


        glBindVertexArray(vertex_array);

       // glDrawArrays(GL_TRIANGLES, 0, 13);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);
    }

    void onDestroy() override {
        program.destroy();
        glDeleteVertexArrays(1, &vertex_array);
    }

    void onImmediateGui(ImGuiIO &io) override {
        //ImGui::Begin("Controls");
        //ImGui::SliderFloat2("Scale", glm::value_ptr(scale), 0, 1);
       // ImGui::SliderFloat2("Translation", glm::value_ptr(translation), -2, 2);
        //ImGui::ColorEdit3("Color", glm::value_ptr(color));
       // ImGui::Checkbox("Vibrate", &vibrate);
        //ImGui::Checkbox("Flicker", &flicker);
        //ImGui::Value("Time: ", (float)glfwGetTime());
        //ImGui::End();
        ImGui::Begin("Keypad");
        ImGui::RadioButton("Shape1",&shape[0]);
        ImGui::RadioButton("Shape2",&shape[1]);
        ImGui::RadioButton("Shape3",&shape[2]);
        ImGui::RadioButton("Shape4",&shape[3]);

        ImGui::End();
    }





};

int main(int argc, char** argv) {
    return UniformsApplication().run();
}
