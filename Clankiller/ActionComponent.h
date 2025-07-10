#pragma once

#include "Base.h"

struct ActionComponent 
{
    Vector2 moveAxis = { 0.0f, 0.0f };
    Vector2 lookDelta = { 0.0f, 0.0f };
};
