#include "../headers/entities.h"

void UpdateInputComponent(InputComponent* input)
{
    input->xInput = 0;
    input->yInput = 0;

    if(IsKeyDown(KEY_A)) input->xInput--;
    if(IsKeyDown(KEY_D)) input->xInput++;
    if(IsKeyDown(KEY_W)) input->yInput--;
    if(IsKeyDown(KEY_S)) input->yInput++;
}