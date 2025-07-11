#pragma once

#include "Base.h"
#include "PlayerComponent.h"
#include "InputStateComponent.h"
#include "TransformComponent.h"
#include "GrabbableComponent.h"
#include "ColliderComponent.h"
#include "ModelComponent.h"
#include "HeldByPlayerComponent.h"

inline void GrabSystem(Registry& registry, float grabDistance = 2.5f, float holdDistance = 2.0f)
{
    // Find the player entity (or entities, if multiplayer were ever a thing).
    auto playerView = registry.view<PlayerComponent, const InputStateComponent, const TransformComponent>();

    for (auto [playerEntity, player, input, playerTransform] : playerView.each())
    {
        // --- Part 1: Handle the Grab/Drop Action on Key Press ---
        // We check `pressedActions` to ensure this logic only runs once per key press.
        if (input.pressedActions.count(GameAction::GrabDrop))
        {
            if (player.holdingEntity == entt::null) // Case 1: Player is not holding anything, so try to GRAB.
            {
                // Find the closest grabbable entity within the specified grab distance.
                Entity closestEntity = entt::null;
                float closestDistSq = grabDistance * grabDistance; // Use squared distance to avoid costly sqrt

                // Iterate through all entities that are marked as grabbable.
                auto grabbableView = registry.view<const TransformComponent, const GrabbableComponent>();
                for (auto [grabEntity, grabTransform] : grabbableView.each())
                {
                    // Ignore objects that might be grabbable but are already being held by someone.
                    if (registry.any_of<HeldByPlayerComponent>(grabEntity)) continue;

                    float distSq = Vector3DistanceSqr(playerTransform.position, grabTransform.position);
                    if (distSq < closestDistSq)
                    {
                        closestDistSq = distSq;
                        closestEntity = grabEntity;
                    }
                }

                // If a suitable entity was found, pick it up.
                if (closestEntity != entt::null)
                {
                    player.holdingEntity = closestEntity;
                    // Add the `HeldByPlayerComponent` tag. This signals to other systems
                    // (like the CollisionSystem) that this entity has special status.
                    registry.emplace<HeldByPlayerComponent>(closestEntity);
                }
            }
            else // Case 2: Player is already holding something, so DROP it.
            {
                Entity heldEntity = player.holdingEntity;
                player.holdingEntity = entt::null; // Clear the player's "holding" state.

                // Remove the `HeldByPlayerComponent` tag from the dropped object.
                // This returns it to its normal, non-held state.
                if (registry.any_of<HeldByPlayerComponent>(heldEntity)) {
                    registry.remove<HeldByPlayerComponent>(heldEntity);
                }
            }
        }

        // --- Part 2: Update the Position of the Held Object Every Frame ---
        // This logic runs continuously as long as the player is holding an object.
        if (player.holdingEntity != entt::null)
        {
            Entity heldEntity = player.holdingEntity;

            // Safety check: ensure the entity we think we're holding is still valid and has a transform.
            if (registry.valid(heldEntity) && registry.all_of<TransformComponent>(heldEntity))
            {
                auto& heldTransform = registry.get<TransformComponent>(heldEntity);

                // Calculate the player's forward direction based on their Y-axis rotation.
                Matrix playerRotationMatrix = MatrixRotateY(playerTransform.rotation.y * DEG2RAD);
                Vector3 forward = Vector3Transform({ 0.0f, 0.0f, 1.0f }, playerRotationMatrix);

                // Calculate the target position for the held object: a fixed distance in front of the player.
                Vector3 holdPosition = Vector3Add(playerTransform.position, Vector3Scale(forward, holdDistance));

                // Directly set the held object's position.
                heldTransform.position = holdPosition;

                // Optional: Lock the rotation of the held object so it doesn't spin wildly.
                heldTransform.rotation = { 0.0f, 0.0f, 0.0f };
            }
            else
            {
                // Failsafe: If the held entity becomes invalid (e.g., destroyed by another system),
                // make the player drop it to prevent crashes.
                player.holdingEntity = entt::null;
            }
        }
    }
}