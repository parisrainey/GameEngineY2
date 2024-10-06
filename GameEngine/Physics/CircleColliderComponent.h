#pragma once
#include "ColliderComponent.h"

namespace GamePhysics
{
	class CircleColliderComponent : public ColliderComponent
	{
	public:
		CircleColliderComponent(float radius) : ColliderComponent() { m_radius = radius; }

		/// <param name="other">Circle Collider colliding with this Circle Collider</param>
		/// <returns>Collision Data</returns>
		GamePhysics::Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		/// <param name="other">AABB Collider colliding with this Circle Collider</param>
		/// <returns>Collision Data</returns>
		GamePhysics::Collision* checkCollisionAABB(AABBColliderComponent* other) override;

		void draw() override;

		float getRadius() { return m_radius; }

	private:
		float m_radius;
	};
}
