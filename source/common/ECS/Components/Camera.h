
#include"ECS/Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


    // An enum for the camera projection type
    enum struct CameraType {
        Orthographic,
        Perspective
    };

    // A class that represents a camera
    // Used to generate a view and a projection matrix
    class Camera: public Component{
    private:
        // Dirty Flags are programming pattern where we only regenerate some output if:
        // 1- The inputs were changed.
        // 2- The output is needed.
        // Where we have flags for whether the View, Projection & ViewProjection matrices needed to be regenerated.


        CameraType type = CameraType::Perspective;

        // The field_of_view_y is in radians and is only used for perspective cameras
        // The orthographic_height is only used for orthographic cameras
        float field_of_view_y = glm::radians(
                90.0f), orthographic_height = 2.0f, aspect_ratio = 1.0f, near = 0.01f, far = 100.0f;

        glm::mat4 V{}, P{}, VP{};

    public:
        static const uint8_t V_DIRTY = 1, P_DIRTY = 2, VP_DIRTY = 4;
        uint8_t dirtyFlags = 0;
        Camera();

        // Setup the camera as a perspective camera
        void setupPerspective(float field_of_view_y, float aspect_ratio, float near, float far);

        // Setup the camera as an orthographic camera
        void setupOrthographic(float orthographic_height, float aspect_ratio, float near, float far);

        void setType(CameraType _type);
        void setOrthographicSize(float orthographic_height);
        void setVerticalFieldOfView(float field_of_view_y);
        void setAspectRatio(float aspect_ratio);
        void setNearPlane(float near);
        void setFarPlane(float far);
        //glm::mat4 getViewMatrix();
        //glm::mat4 getVPMatrix();


        glm::mat4 getProjectionMatrix();



        CameraType getType();
        [[nodiscard]] float getVerticalFieldOfView() const ;
        [[nodiscard]] float getHorizontalFieldOfView() const ;
        [[nodiscard]] float getOrthographicHeight() const ;
        [[nodiscard]] float getOrthographicWidth() const ;
        [[nodiscard]] float getAspectRatio() const ;
        [[nodiscard]] float getNearPlane() const ;
        [[nodiscard]] float getFarPlane() const ;

        ~Camera(){

        }
};