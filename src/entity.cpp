#include "../headers/entity.h"

void UpdateInputComponent(InputComponent input)
{
    if(IsKeyDown(KEY_A)) input.xInput--;
    if(IsKeyDown(KEY_D)) input.xInput++;
    if(IsKeyDown(KEY_W)) input.yInput--;
    if(IsKeyDown(KEY_S)) input.yInput++;
}