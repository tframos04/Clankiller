#pragma once

#include "Base.h"
#include "GameAction.h"

struct InputStateComponent 
{
    std::set<GameAction> activeActions;
    std::set<GameAction> pressedActions; // <-- New set for single-press actions
    std::map<GameAction, float> actionValues;
};
