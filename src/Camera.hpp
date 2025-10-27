#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
		glm::vec3 position = glm::vec3(0);
		glm::vec3 position_cache;

		glm::vec3 direction;
		glm::vec3 direction_cache;

		glm::mat4 view;
		glm::mat4 projection;

		glm::vec3 up, right;

		float pitch;
		float yaw;
	public:

		Camera();
		~Camera();

		void SetOrthographicProjection(const float left, const float right, const float bottom, const float top);
		void SetPerspectiveProjection(const float fov, const float aspect, const float near, const float far);

		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetViewMatrix();
		glm::vec3 GetDirection() const;
		glm::vec3 GetRightVec() const;

		void Move(const glm::vec3& position);
		void MoveTo(const glm::vec3& position);

		void LookAt(const glm::vec3& center);
		void Turn(const float pitch_angle, const float yaw_angle);
};
