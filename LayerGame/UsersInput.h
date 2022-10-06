#pragma once

static enum InputInfo { MOVE_UP, MOVE_DOWN, MOVE_RIGHT, MOVE_LEFT };

void InputUpdate();

bool JustInput(int KeyCode);
bool Input(int KeyCode);
bool JustOut(int KeyCode);

bool Press(int KeyCode);