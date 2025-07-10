#pragma once

#include "Base.h"
#include "TransformComponent.h"
#include "PlayerComponent.h"

inline void CameraSystem(Registry& registry, Camera3D& camera) 
{
    auto view = registry.view<const PlayerComponent, const TransformComponent>();

    for (auto [entity, transform] : view.each()) 
    {
        camera.position = transform.position;

        Matrix fullRotationMatrix = MatrixMultiply(
            MatrixRotateX(transform.rotation.x * DEG2RAD),
            MatrixRotateY(transform.rotation.y * DEG2RAD)
        );
        Vector3 forward = Vector3Transform({ 0.0f, 0.0f, 1.0f }, fullRotationMatrix);

        camera.target = Vector3Add(camera.position, forward);
        break;
    }
}
