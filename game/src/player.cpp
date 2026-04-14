#include "../game/headers/player.h"

void MoveEntity(Player* player) //this is EXTREMELY temporary
{
    player->moveComponent.velocity = Vector2{player->inputComponent.xInput * player->speed * GetFrameTime(), 
        player->inputComponent.yInput * player->speed * GetFrameTime()};


    player->position.x = player->position.x + player->moveComponent.velocity.x;
    player->position.y = player->position.y + player->moveComponent.velocity.y;

    player->textureComponent.position = player->position;
}