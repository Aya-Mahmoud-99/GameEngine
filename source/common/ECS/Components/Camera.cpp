//
// Created by Aya on 11/18/2020.
//

#include "Camera.h"
Camera::Camera(){
    dirtyFlags = V_DIRTY | P_DIRTY | VP_DIRTY;
}

// Setup the camera as a perspective camera
void Camera::setupPerspective(float field_of_view_y, float aspect_ratio, float near, float far){
    this->type = CameraType::Perspective;
    this->field_of_view_y = field_of_view_y;
    this->aspect_ratio = aspect_ratio;
    this->near = near;
    this->far = far;
    dirtyFlags |= P_DIRTY | VP_DIRTY; // Both P & VP need to be regenerated
}

// Setup the camera as an orthographic camera
void Camera::setupOrthographic(float orthographic_height, float aspect_ratio, float near, float far){
    this->type = CameraType::Orthographic;
    this->orthographic_height = orthographic_height;
    this->aspect_ratio = aspect_ratio;
    this->near = near;
    this->far = far;
    dirtyFlags |= P_DIRTY | VP_DIRTY; // Both P & VP need to be regenerated
}

void Camera::setType(CameraType _type){
    if(this->type != _type){
        dirtyFlags |= P_DIRTY | VP_DIRTY;
        this->type = _type;
    }
}
void Camera::setOrthographicSize(float orthographic_height){
    if(this->orthographic_height != orthographic_height){
        dirtyFlags |= P_DIRTY | VP_DIRTY;
        this->orthographic_height = orthographic_height;
    }
}
void Camera::setVerticalFieldOfView(float field_of_view_y){
    if(this->field_of_view_y != field_of_view_y){
        dirtyFlags |= P_DIRTY | VP_DIRTY;
        this->field_of_view_y = field_of_view_y;
    }
}
void Camera::setAspectRatio(float aspect_ratio){
    if(this->aspect_ratio != aspect_ratio){
        dirtyFlags |= P_DIRTY | VP_DIRTY;
        this->aspect_ratio = aspect_ratio;
    }
}
void Camera::setNearPlane(float near){
    if(this->near != near){
        dirtyFlags |= P_DIRTY | VP_DIRTY;
        this->near = near;
    }
}
void Camera::setFarPlane(float far){
    if(this->far != far){
        dirtyFlags |= P_DIRTY | VP_DIRTY;
        this->far = far;
    }
}



glm::mat4 Camera::getProjectionMatrix(){
    if(dirtyFlags & P_DIRTY){ // Only regenerate the projection matrix if its flag is dirty
        if(type == CameraType::Orthographic){
            float half_height = orthographic_height * 0.5f;
            float half_width = aspect_ratio * half_height;
            P = glm::ortho(-half_width, half_width, -half_height, half_height, near, far);
        } else {
            P = glm::perspective(field_of_view_y, aspect_ratio, near, far);
        }
        dirtyFlags &= ~P_DIRTY; // P is no longer dirty
    }
    return P;
}



CameraType Camera::getType(){return type;}
[[nodiscard]] float Camera::getVerticalFieldOfView() const {return field_of_view_y;}
[[nodiscard]] float Camera::getHorizontalFieldOfView() const {return field_of_view_y * aspect_ratio;}
[[nodiscard]] float Camera::getOrthographicHeight() const {return orthographic_height;}
[[nodiscard]] float Camera::getOrthographicWidth() const {return orthographic_height * aspect_ratio;}
[[nodiscard]] float Camera::getAspectRatio() const {return aspect_ratio;}
[[nodiscard]] float Camera::getNearPlane() const {return near;}
[[nodiscard]] float Camera::getFarPlane() const {return far;}

