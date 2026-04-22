#include "../game/headers/gameEntities.h"

void MoveEntity(Player* player) //this is EXTREMELY temporary
{
    player->moveComponent.velocity = Vector2{player->inputComponent.xInput * player->speed * GetFrameTime(), 
        player->inputComponent.yInput * player->speed * GetFrameTime()};


    player->position.x = player->position.x + player->moveComponent.velocity.x;
    player->position.y = player->position.y + player->moveComponent.velocity.y;

    player->textureComponent.position = player->position;
}

void CreateGameEntities(entt::registry& registry)
{
    entt::entity player = registry.create();
    registry.emplace<TextureComponent>(player, screenWidth / 2.0f, screenHeight / 2.0f);

    här


    player.textureComponent.texture.width = 150;
    player.textureComponent.texture.height = 80;
    player.position = Vector2{100, 80};
    player.speed = 125;
    SetTexture(&player.textureComponent.texture, "game/assets/textures/HumanoidTpose.png");
}