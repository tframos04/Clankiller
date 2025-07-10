#pragma once

#include "Base.h"
#include "InputMapping.h"
#include "InputStateComponent.h"

inline void InputSystem(Registry& registry, const InputMapping& mapping) 
{
    auto view = registry.view<InputStateComponent>();

    for (auto [entity, state] : view.each()) 
    {
        state.activeActions.clear();
        state.actionValues.clear();

        for (const auto& [key, action] : mapping.keyActionMap) 
        {
            if (IsKeyDown(key)) 
            {
                state.activeActions.insert(action);
            }
        }

        Vector2 mouseDelta = GetMouseDelta();
        if (mapping.analogActionMap.count(InputSource::MouseX)) 
        {
            GameAction action = mapping.analogActionMap.at(InputSource::MouseX);
            state.actionValues[action] = mouseDelta.x * mapping.mouseSensitivity;
        }

        if (mapping.analogActionMap.count(InputSource::MouseY)) 
        {
            GameAction action = mapping.analogActionMap.at(InputSource::MouseY);
            state.actionValues[action] = mouseDelta.y * mapping.mouseSensitivity;
        }
    }
}
