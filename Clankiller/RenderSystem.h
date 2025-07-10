#pragma once

#include "TransformComponent.h"
#include "ModelComponent.h"

static inline void onEnterSystem(const Camera3D& camera)
{
	BeginDrawing();
	ClearBackground(WHITE);
	BeginMode3D(camera);
}

static inline void onExitSystem()
{
	EndMode3D();
	EndDrawing();
}

inline void RenderSystem(Registry& registry, const Camera3D& camera)
{
	onEnterSystem(camera);
	
	auto view = registry.view<const TransformComponent, const ModelComponent>();

	for (auto [entity, transform, model] : view.each())
	{
		rlPushMatrix();

		rlTranslatef(transform.position.x, transform.position.y, transform.position.z);

		rlRotatef(transform.rotation.z, 0.0f, 0.0f, 1.0f); 
		rlRotatef(transform.rotation.y, 0.0f, 1.0f, 0.0f); 
		rlRotatef(transform.rotation.x, 1.0f, 0.0f, 0.0f); 

		rlScalef(transform.scale.x, transform.scale.y, transform.scale.z);

		DrawModel(model.model, { 0.0f, 0.0f, 0.0f }, 1.0f, model.tint);

		rlPopMatrix();
	}

	onExitSystem();
}