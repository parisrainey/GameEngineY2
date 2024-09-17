#include "ColliderComponent.h"

void GamePhysics::ColliderComponent::start()
{
	//Add collider to the scene
	//Get owner's rigidbody
}

GamePhysics::Collision* GamePhysics::ColliderComponent::checkCollision(ColliderComponent* other)
{
	switch (other->getColliderType())
	{
	case Circle:
		return checkCollisionCircle((CircleColliderComponent*)other);
	case AABB:
		return checkCollisionAABB((AABBColliderComponent*)other);
	}

	return nullptr;
}

void GamePhysics::ColliderComponent::onCollisionEnter(GamePhysics::Collision* other)
{
	m_color = 0xFF0000FF;
}

void GamePhysics::ColliderComponent::update(double deltaTime)
{
	m_color = 0x00FF00FF;
}
