#pragma once

#include "Base.h"
#include "LightComponent.h"
#include "TransformComponent.h"

inline Entity createPointLight(Registry& registry, Shader& shader, Vector3 position, Color color)
{
    const auto entity = registry.create();

    Light light = CreateLight(LIGHT_POINT, position, Vector3Zero(), color, shader);

    if (light.enabledLoc <= 0) {
        registry.destroy(entity); 
        TraceLog(LOG_WARNING, "RLIGHTS: Failed to create new light, MAX_LIGHTS likely reached.");
        return entt::null;
    }

    registry.emplace<LightComponent>(entity, light);
    registry.emplace<TransformComponent>(entity, position, Vector3{ 0,0,0 }, Vector3{ 1,1,1 });

    return entity;
}