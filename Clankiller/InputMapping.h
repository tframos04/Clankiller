#pragma once

#include "Base.h"
#include "GameAction.h"
#include "InputSource.h"

struct InputMapping {
    std::map<int, GameAction> keyActionMap;
    std::map<InputSource, GameAction> analogActionMap;
    float mouseSensitivity = 0.1f;

    InputMapping() {
        keyActionMap[KEY_W] = GameAction::MoveForward;
        keyActionMap[KEY_S] = GameAction::MoveBack;
        keyActionMap[KEY_A] = GameAction::MoveLeft;
        keyActionMap[KEY_D] = GameAction::MoveRight;

        analogActionMap[InputSource::MouseX] = GameAction::LookX;
        analogActionMap[InputSource::MouseY] = GameAction::LookY;
        keyActionMap[KEY_E] = GameAction::GrabDrop; // <-- Map the key
    }
};