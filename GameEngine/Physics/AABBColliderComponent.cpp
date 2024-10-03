#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Engine/Entity.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include <raylib.h>

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;
    float otherRadius = other->getRadius();

    return nullptr;
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
