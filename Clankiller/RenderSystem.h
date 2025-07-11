#pragma once

#include "TransformComponent.h"
#include "ModelComponent.h"


inline void RenderSystem(Registry& registry, const Camera3D& camera)
{
	BeginDrawing();
	ClearBackground(DARKGRAY); // A darker background shows lighting better

	// --- UPDATE SHADER UNIFORMS ---
	// For every shader that needs it, update the camera position.
	// We get the first model's shader, assuming all models use the same one for now.
	auto viewForShader = registry.view<const ModelComponent>();
	if (!viewForShader.empty()) {
		entt::entity firstEntity = viewForShader.front();
		Shader shader = viewForShader.get<const ModelComponent>(firstEntity).model.materials[0].shader;

		// Send the camera position to the shader
		SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], &camera.position, SHADER_UNIFORM_VEC3);
	}

	BeginMode3D(camera);
	DrawGrid(200, 1.0f);

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

	EndMode3D();
	DrawFPS(10, 10);
	EndDrawing();
}
