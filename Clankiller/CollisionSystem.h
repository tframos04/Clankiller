#pragma once

#include "Base.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

inline BoundingBox GetWorldBoundingBox(const TransformComponent& transform, const ColliderComponent& collider) {
    BoundingBox worldBox = collider.box;
    worldBox.min = Vector3Add(worldBox.min, transform.position);
    worldBox.max = Vector3Add(worldBox.max, transform.position);
    return worldBox;
}

inline void CollisionSystem(Registry& registry)
{
    auto view = registry.view<TransformComponent, const ColliderComponent>();

    // This is an O(n^2) check. For a few entities, it's fine.
    // For many entities, a spatial partitioning structure (e.g., a grid) would be needed.
    for (auto [entityA, transformA, colliderA] : view.each())
    {
        for (auto [entityB, transformB, colliderB] : view.each())
        {
            // Don't check an entity against itself
            if (entityA == entityB) continue;

            // To avoid checking and resolving every pair twice (A-B and B-A),
            // we can just check one way. This ensures resolution only happens once.
            if (entityA > entityB) continue;

            BoundingBox boxA = GetWorldBoundingBox(transformA, colliderA);
            BoundingBox boxB = GetWorldBoundingBox(transformB, colliderB);

            if (CheckCollisionBoxes(boxA, boxB))
            {
                // Collision detected! Now we need to resolve it by pushing them apart.

                // Calculate penetration depth on each axis
                float overlapX = (boxA.max.x - boxA.min.x) / 2.0f + (boxB.max.x - boxB.min.x) / 2.0f - fabsf(transformA.position.x - transformB.position.x);
                float overlapZ = (boxA.max.z - boxA.min.z) / 2.0f + (boxB.max.z - boxB.min.z) / 2.0f - fabsf(transformA.position.z - transformB.position.z);

                // We resolve on the axis with the smallest overlap (least penetration)
                if (overlapX < overlapZ)
                {
                    // Resolve on X axis
                    float resolve = (transformA.position.x > transformB.position.x) ? overlapX : -overlapX;
                    transformA.position.x += resolve / 2.0f;
                    transformB.position.x -= resolve / 2.0f;
                }
                else
                {
                    // Resolve on Z axis
                    float resolve = (transformA.position.z > transformB.position.z) ? overlapZ : -overlapZ;
                    transformA.position.z += resolve / 2.0f;
                    transformB.position.z -= resolve / 2.0f;
                }
            }
        }
    }
}