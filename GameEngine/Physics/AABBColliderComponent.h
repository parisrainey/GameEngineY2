#pragma once
#include "ColliderComponent.h"

namespace GamePhysics
{
	class AABBColliderComponent : public ColliderComponent
	{
	public:
		AABBColliderComponent(float width, float height) : ColliderComponent() { m_width = width, m_height = height; }

		
		/// <param name="other">Circle Collider colliding with AABB</param>
		/// <returns>Collision Data</returns>
		GamePhysics::Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		/// <param name="other">AABB collider colliding with Circle</param>
		/// <returns>Collision Data</returns>
		GamePhysics::Collision* checkCollisionAABB(AABBColliderComponent* other) override;

		void draw() override;

		float getWidth() { return m_width; }
		float getHeight() { return m_height; }

	private:
		float m_width;
		float m_height;
	};
}