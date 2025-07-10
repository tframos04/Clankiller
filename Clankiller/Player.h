#pragma once

#include "Base.h"
#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "ModelComponent.h"

inline Entity createPlayer(Registry& registry, Model model, Vector3 position)
{
	const auto entity = registry.create();
	const Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	const Vector3 scale = { 1.0f, 1.0, 1.0f };

	registry.emplace<PlayerComponent>(entity);
	registry.emplace<TransformComponent>(entity, position, rotation, scale);
	registry.emplace<ModelComponent>(entity, model, BLUE);

	return entity;
}