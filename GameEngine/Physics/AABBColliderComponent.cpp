#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Engine/Entity.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include <raylib.h>

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    // Holds information for other collider's position
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    // Holds information for our position
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    // Holds direction from us to other collider
    GameMath::Vector2 direction = otherPosition - position;
    // Distance between us and other collider on the X
    float distanceX = otherPosition.x - position.x;
    // Distance between us and other collider on the Y
    float distanceY = otherPosition.y - position.y;
    // Holds other collider radius
    float otherRadius = other->getRadius();
    // Holds temporary radius for us to collide with circle
    float radius = m_width / 2;

    // If other radius is not same or less than our radius, return
    if (!otherRadius <= radius)
        return nullptr;

    GamePhysics::Collision* collisionData = new Collision();
    collisionData->collider = other;
    // If other radius not equal to or less than ours AND distance X more than distance Y
    if (otherRadius <= radius && distanceX > distanceY)
    {
        // Check if direction Y more than zero
        if (direction.y > 0)
        {
            // Set normal to be positive y
            collisionData->normal = GameMath::Vector2(0, 1);
        }
        // If direction Y not more than zero
        else
            
            collisionData->normal = GameMath::Vector2(0, -1);

        // Set penetration distance to be y
        collisionData->penetrationDistance = distanceY;
    }
    else
    {
        // Check if direction X more than zero
        if (direction.x > 0)
        {
            // Set normal to be positive x
            collisionData->normal = GameMath::Vector2(1, 0);
        }
        // If direction x not more than zero
        else
            // Set normal to be negative x
            collisionData->normal = GameMath::Vector2(-1, 0);

        // Set penetration distance to be x
        collisionData->penetrationDistance = distanceX;
    }
    if (collisionData->normal.y > collisionData->normal.x)
    {
        collisionData->contactPoint = position + collisionData->normal * m_height / 2;
    }
    else
        collisionData->contactPoint = position + collisionData->normal * m_width / 2;
        return collisionData;

}

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;
    float distanceX = otherPosition.x - position.x;
    float distanceY = otherPosition.y - position.y;

    if (direction.x > m_width + other->getWidth() || direction.y > m_height + other->getHeight())
        return nullptr;

    GamePhysics::Collision* collisionData = new Collision();
    collisionData->collider = other;
    if (distanceX > distanceY)
    {
        if (direction.y > 0)
        {
            collisionData->normal = GameMath::Vector2(0, 1);
        }
        else
            collisionData->normal = GameMath::Vector2(0, -1);
        
        collisionData->penetrationDistance = distanceY;
    }
    else
    {
        if (direction.x > 0)
        {
            collisionData->normal = GameMath::Vector2(1, 0);
        }
        else
            collisionData->normal = GameMath::Vector2(-1, 0);

        collisionData->penetrationDistance = distanceX;
    }
    if (collisionData->normal.y > collisionData->normal.x)
    {
        collisionData->contactPoint = position + collisionData->normal * m_height/2;
    }
    else
        collisionData->contactPoint = position + collisionData->normal * m_width / 2;

    return collisionData;
}

void GamePhysics::AABBColliderComponent::draw()
{
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

    RAYLIB_H::DrawRectangleLines(position.x, position.y, m_width, m_height,GetColor(getColor()));
}
