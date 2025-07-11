#pragma once

#include "Base.h"
#include "LightComponent.h"
#include "TransformComponent.h"

inline void LightingSystem(Registry& registry, Shader& shader)
{
    auto view = registry.view<LightComponent, const TransformComponent>();

    for (auto [entity, light, transform] : view.each())
    {
        light.light.position = transform.position;

        UpdateLightValues(shader, light.light);
    }
}