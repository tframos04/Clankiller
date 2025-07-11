#pragma once

#include "Base.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "HeldByPlayerComponent.h"

inline BoundingBox GetWorldBoundingBox(const TransformComponent& transform, const ColliderComponent& collider) {
    BoundingBox worldBox = collider.box;
    worldBox.min = Vector3Add(worldBox.min, transform.position);
    worldBox.max = Vector3Add(worldBox.max, transform.position);
    return worldBox;
}

inline void CollisionSystem(Registry& registry)
{
    auto view = registry.view<TransformComponent, const ColliderComponent>();

    for (auto [entityA, transformA, colliderA] : view.each())
    {
        for (auto [entityB, transformB, colliderB] : view.each())
        {
            if (entityA >= entityB) continue; // Avoid self-collision and double checks

            // --- NEW COLLISION RULES ---

            bool isAHeld = registry.any_of<HeldByPlayerComponent>(entityA);
            bool isBHeld = registry.any_of<HeldByPlayerComponent>(entityB);
            bool isAPlayer = registry.any_of<PlayerComponent>(entityA);
            bool isBPlayer = registry.any_of<PlayerComponent>(entityB);

            // Rule 1: Ignore collision between the player and the object they are holding.
            if ((isAPlayer && isBHeld) || (isBPlayer && isAHeld))
            {
                continue; // Skip this collision check
            }

            BoundingBox boxA = GetWorldBoundingBox(transformA, colliderA);
            BoundingBox boxB = GetWorldBoundingBox(transformB, colliderB);

            if (CheckCollisionBoxes(boxA, boxB))
            {
                // Calculate penetration depth
                float overlapX = (boxA.max.x - boxA.min.x) / 2.0f + (boxB.max.x - boxB.min.x) / 2.0f - fabsf(transformA.position.x - transformB.position.x);
                float overlapZ = (boxA.max.z - boxA.min.z) / 2.0f + (boxB.max.z - boxB.min.z) / 2.0f - fabsf(transformA.position.z - transformB.position.z);

                // --- NEW RESOLUTION LOGIC ---

                // Rule 2: If one object is held, it's "immovable" and only pushes the other object.
                if (isAHeld) { // Object A is held by the player
                    // Push only B
                    if (overlapX < overlapZ) {
                        float resolve = (transformA.position.x > transformB.position.x) ? -overlapX : overlapX;
                        transformB.position.x += resolve;
                    }
                    else {
                        float resolve = (transformA.position.z > transformB.position.z) ? -overlapZ : overlapZ;
                        transformB.position.z += resolve;
                    }
                }
                else if (isBHeld) { // Object B is held by the player
                    // Push only A
                    if (overlapX < overlapZ) {
                        float resolve = (transformB.position.x > transformA.position.x) ? -overlapX : overlapX;
                        transformA.position.x += resolve;
                    }
                    else {
                        float resolve = (transformB.position.z > transformA.position.z) ? -overlapZ : overlapZ;
                        transformA.position.z += resolve;
                    }
                }
                else {
                    // Original behavior: Push both objects apart equally.
                    if (overlapX < overlapZ) {
                        float resolve = (transformA.position.x > transformB.position.x) ? overlapX : -overlapX;
                        transformA.position.x += resolve / 2.0f;
                        transformB.position.x -= resolve / 2.0f;
                    }
                    else {
                        float resolve = (transformA.position.z > transformB.position.z) ? overlapZ : -overlapZ;
                        transformA.position.z += resolve / 2.0f;
                        transformB.position.z -= resolve / 2.0f;
                    }
                }
            }
        }
    }
}