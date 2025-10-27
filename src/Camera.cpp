#include "Camera.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include <iostream>

Camera::Camera() {
	yaw = 0;
	pitch = 0;
    right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
    up = glm::cross(right, direction);
	direction = glm::normalize(glm::vec3(
			cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
			sin(glm::radians(pitch)),			
			sin(glm::radians(yaw)) * cos(glm::radians(pitch))
			));
}
Camera::~Camera() { }

void Camera::SetOrthographicProjection(const float left, const float right, const float bottom, const float top) {
	projection = glm::ortho(left, right, bottom, top);
}

void Camera::SetPerspectiveProjection(const float fov, const float aspect, const float near, const float far) {
	projection = glm::perspective(fov, aspect, near, far);
}

glm::mat4 Camera::GetProjectionMatrix() const {
	return projection;
};

glm::mat4 Camera::GetViewMatrix() {
	if (position != position_cache || direction != direction_cache) {
		view = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));

		position_cache = position;
		direction_cache = direction;
	}
	return view;
}

glm::vec3 Camera::GetDirection() const {
	return direction;
}

glm::vec3 Camera:: GetRightVec() const {
	return right;
}

void Camera::Move(const glm::vec3& vector) {
    position += vector.z * direction;
    position += vector.x * right;
    position += vector.y * up;
}

void Camera::MoveTo(const glm::vec3& position) {
	this->position = position;
}

void Camera::LookAt(const glm::vec3& center) {
	direction = glm::normalize(center - position);

	pitch = glm::degrees(asin(direction.y));
    yaw = glm::degrees(atan2(direction.z, direction.x));

	right = glm::normalize(glm::cross(direction, glm::vec3(0,1,0)));
	up = glm::cross(right, direction);
}

void Camera::Turn(const float pitch_angle, const float yaw_angle) {
	if (pitch_angle == 0 && yaw_angle == 0) return;


	yaw += yaw_angle;

	pitch += pitch_angle;
	if(pitch > 89.0f) pitch =  89.0f;
	if(pitch < -89.0f) pitch = -89.0f;

	direction = glm::normalize(glm::vec3(
			cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
			sin(glm::radians(pitch)),			
			sin(glm::radians(yaw)) * cos(glm::radians(pitch))
			));

	if (yaw != 0) right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
	if (pitch != 0) up = glm::normalize(glm::cross(right, direction));
}
