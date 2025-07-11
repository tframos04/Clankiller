#pragma once

#include "Base.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "ColliderComponent.h"
#include "GrabbableComponent.h"

inline Entity createGrabbableCube(Registry& registry, Vector3 position)
{
    const auto entity = registry.create();

    registry.emplace<TransformComponent>(entity, position, Vector3{ 0,0,0 }, Vector3{ 0.4,0.4, 0.4 });
    registry.emplace<GrabbableComponent>(entity);

    auto& assets = AssetManager::getInstance();
    Model model = assets.models.get("cube"); // Or a real cube model if you have one
    model.materials[0].shader = assets.shaders.get("lighting");
    registry.emplace<ModelComponent>(entity, model, YELLOW); // Make it yellow to stand out

    // Grabbable items should also be collidable
    registry.emplace<ColliderComponent>(entity, GetModelBoundingBox(model));

    return entity;
}