#pragma once

#include "Base.h"
#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "ActionComponent.h"
#include "InputStateComponent.h"
#include "ModelComponent.h"
#include "ColliderComponent.h"
#include "AssetManager.h"

inline Entity createPlayer(Registry& registry, Vector3 position)
{
	const auto entity = registry.create();
	const Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	const Vector3 scale = { 1.0f, 3.0, 1.0f };

	registry.emplace<PlayerComponent>(entity);
	registry.emplace<TransformComponent>(entity, position, rotation, scale);
	registry.emplace<ActionComponent>(entity);
	registry.emplace<InputStateComponent>(entity);

	auto& assets = AssetManager::getInstance();
	Model model = assets.models.get("cube");
	model.materials[0].shader = assets.shaders.get("lighting");
	registry.emplace<ModelComponent>(entity, model, WHITE);
	registry.emplace<ColliderComponent>(entity, GetModelBoundingBox(model));

	return entity;

	return entity;
}
