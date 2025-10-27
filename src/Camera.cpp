#include "Camera.hpp"
#include "glm/fwd.hpp"

Camera::Camera() { }
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
	position += vector;
};

void Camera::MoveTo(const glm::vec3& position) {
	this->position = position;
}

void Camera::LookAt(const glm::vec3& center) {
	direction = glm::normalize(center - position);
}

void Camera::TurnYaw(const float angle) {
	if (angle == 0) return;

    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, up);
    direction = glm::normalize(glm::vec3(rot * glm::vec4(direction, 0.0f)));
    right = glm::normalize(glm::cross(direction, up));
}

void Camera::TurnPitch(float angle) {
	if (angle == 0) return;

	float new_pitch = glm::clamp(pitch + angle, min_pitch, max_pitch);
	angle = new_pitch - pitch;
	pitch = new_pitch;

    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, right);
    direction = glm::normalize(glm::vec3(rot * glm::vec4(direction, 0.0f)));
}
