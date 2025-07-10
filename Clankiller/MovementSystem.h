#pragma once

#include "Base.h"
#include "ActionComponent.h"
#include "TransformComponent.h"

inline void MovementSystem(Registry& registry, float deltaTime) 
{
    auto view = registry.view<TransformComponent, const ActionComponent>();

    for (auto [entity, transform, action] : view.each()) {
        transform.rotation.y -= action.lookDelta.x;

        transform.rotation.x += action.lookDelta.y;

        if (transform.rotation.x > 89.0f) transform.rotation.x = 89.0f;
        if (transform.rotation.x < -89.0f) transform.rotation.x = -89.0f;

        if (Vector2LengthSqr(action.moveAxis) > 0.0f) 
        {
            float speed = 5.0f * deltaTime;
            Vector3 direction = { action.moveAxis.x, 0.0f, action.moveAxis.y };

            Matrix rotationMatrix = MatrixRotateY(transform.rotation.y * DEG2RAD);
            Vector3 moveVector = Vector3Transform(direction, rotationMatrix);

            transform.position = Vector3Add(transform.position, Vector3Scale(Vector3Normalize(moveVector), speed));
        }
    }
}
