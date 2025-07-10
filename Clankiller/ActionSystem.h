#pragma once

#include "Base.h"
#include "InputStateComponent.h"
#include "ActionComponent.h"

inline void ActionSystem(Registry& registry)
{
    auto view = registry.view<const InputStateComponent, ActionComponent>();

    for (auto [entity, state, action] : view.each())
    {
        action.moveAxis = { 0.0f, 0.0f };
        action.lookDelta = { 0.0f, 0.0f };

        if (state.activeActions.count(GameAction::MoveForward)) action.moveAxis.y = 1.0f;
        if (state.activeActions.count(GameAction::MoveBack)) action.moveAxis.y = -1.0f;
        if (state.activeActions.count(GameAction::MoveLeft)) action.moveAxis.x = 1.0f;
        if (state.activeActions.count(GameAction::MoveRight)) action.moveAxis.x = -1.0f;

        if (state.actionValues.count(GameAction::LookX)) 
        {
            action.lookDelta.x = state.actionValues.at(GameAction::LookX);
        }

        if (state.actionValues.count(GameAction::LookY)) 
        {
            action.lookDelta.y = state.actionValues.at(GameAction::LookY);
        }
    }
}
