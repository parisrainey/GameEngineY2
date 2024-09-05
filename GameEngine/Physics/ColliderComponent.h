#pragma once
#include "Engine/Component.h"
#include "Math/Vector2.h"

namespace GamePhysics
{
	class CircleColliderComponent;
	class AABBColliderComponent;
	class RigidBodyComponent;

	class ColliderComponent : public GameEngine::Component
	{
	public:
		enum ColliderType
		{
			Circle,
			AABB
		};

		void start() override;
		Collision* checkCollision(ColliderComponent* other);

		virtual Collision* checkCollisionCircle(CircleColliderComponent* other) = 0;
		virtual Collision* checkCollisionAABB(AABBColliderComponent* other) = 0;

	private:
		bool m_isTrigger;
		ColliderType m_colliderType;
		unsigned int m_color = 0x00FF00FF;
		RigidBodyComponent* m_rigidBody;
	};

	struct Collision
	{
	public:
		GameMath::Vector2 normal;
		ColliderComponent* collider;
		GameMath::Vector2 contactPoint;
		float penetrationDistance;
	};
}
