#pragma once

#include "Base.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "ColliderComponent.h"

inline Entity createEnemy(Registry& registry, Vector3 position)
{
	const auto entity = registry.create();
	const Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	const Vector3 scale = { 1.0f, 1.0, 1.0f };

	Model& model = AssetManager::getInstance().models.get("cube");

	registry.emplace<TransformComponent>(entity, position, rotation, scale);
	registry.emplace<ModelComponent>(entity, model, RED);
	registry.emplace<ColliderComponent>(entity, GetModelBoundingBox(model));

	return entity;
}
