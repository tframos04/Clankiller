#pragma once

#include "Base.h"
#include "GameAction.h"

struct InputStateComponent 
{
    std::set<GameAction> activeActions;
    std::map<GameAction, float> actionValues;
};
