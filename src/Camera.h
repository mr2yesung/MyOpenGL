#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

enum class MovementDirection {
	FORWARD = 0,
	BACKWARD = 1,
	LEFT = 2,
	RIGHT = 3
};

struct CameraDirections {
	glm::vec3 frontVector;
	glm::vec3 rightVector;
	glm::vec3 upVector;
};

class Camera {
private:
	glm::vec3 cameraPos;

	CameraDirections cameraDirections;

	const glm::vec3 worldUpVector;
	
	float cameraYaw;
	float cameraPitch;

	float cameraZoom;

	const float rotateSensitivity;
	const float velocity;
public:
	Camera(const glm::vec3& cameraPos = glm::vec3(0.0f, 0.0f, 3.0f), const float cameraYaw = 0.0f, const float cameraPitch = 0.0f);

	inline const glm::mat4 GetViewMatrix() const { return glm::lookAt(cameraPos, cameraPos + cameraDirections.frontVector, cameraDirections.upVector); }

	void RotateCamera(const float deltaX, const float deltaY);

	void MoveCamera(const MovementDirection direction);

	void ScrollCamera(float deltaScroll);
	inline const float GetCameraZoom() const { return cameraZoom; }
private:
	void UpdateCameraVectors();
};