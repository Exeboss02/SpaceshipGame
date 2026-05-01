#pragma once
#include <type_traits>
#include <iostream>
#include <raylib.h>
#include <vector>

#include "../headers/entt.hpp"

struct TextureContainer
{
    Texture2D texture = {};
    std::string path = "";
};

struct TextureStorage
{
    TextureStorage() = default;
    ~TextureStorage();

    std::vector<TextureContainer*> textures;
};

struct AudioStorage
{
    //sound
};