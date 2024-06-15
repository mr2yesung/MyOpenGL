#include "Camera.h"

Camera::Camera(const glm::vec3& cameraPos, const float cameraYaw, const float cameraPitch)
	:cameraPos(cameraPos), cameraYaw(cameraYaw), cameraPitch(cameraPitch), worldUpVector(glm::vec3(0.0f, 1.0f, 0.0f)), rotateSensitivity(0.15f), velocity(0.1f), cameraZoom(45.0f)
{
	UpdateCameraVectors();
}

void Camera::RotateCamera(const float deltaX, const float deltaY)
{
	cameraYaw += deltaX * rotateSensitivity;
	cameraPitch += deltaY * rotateSensitivity;

	if (cameraPitch > 89.5f)
		cameraPitch = 89.5f;
	else if (cameraPitch < -89.5f)
		cameraPitch = -89.5f;

	UpdateCameraVectors();
}

void Camera::MoveCamera(const MovementDirection direction)
{
	switch (direction)
	{
	case MovementDirection::FORWARD:
		cameraPos += cameraDirections.frontVector * velocity;
		break;

	case MovementDirection::BACKWARD:
		cameraPos -= cameraDirections.frontVector * velocity;
		break;

	case MovementDirection::LEFT:
		cameraPos -= cameraDirections.rightVector * velocity;
		break;

	case MovementDirection::RIGHT:
		cameraPos += cameraDirections.rightVector * velocity;
		break;
	}
}

void Camera::ScrollCamera(float deltaScroll)
{
	cameraZoom -= deltaScroll;

	if (cameraZoom < 1.0f)
		cameraZoom = 1.0f;
	else if (cameraZoom > 45.0f)
		cameraZoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 updatedFrontVector;
	updatedFrontVector.x = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	updatedFrontVector.y = sin(glm::radians(cameraPitch));
	updatedFrontVector.z = -cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));

	cameraDirections.frontVector = glm::normalize(updatedFrontVector);
	cameraDirections.rightVector = glm::normalize(glm::cross(cameraDirections.frontVector, worldUpVector));
	cameraDirections.upVector = glm::normalize(glm::cross(cameraDirections.rightVector, cameraDirections.frontVector));
}
