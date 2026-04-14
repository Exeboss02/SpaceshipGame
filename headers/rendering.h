#pragma once
#include <raylib.h>
#include <iostream>
#include "../headers/entity.h"

void Draw(TextureComponent* textureEntity)
{
    DrawTextureV(textureEntity->texture, {textureEntity->position}, WHITE);
}

void SetTexture(Texture2D* texture, std::string path)
{
    if(!texture)
    {
        std::cout << "texture was nullptr" << std::endl;
        return;
    }

    int width = texture->width;
    int height = texture->height;
    *texture = LoadTexture(path.c_str());
    texture->width = width;
    texture->height = height;
}