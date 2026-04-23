#pragma once
#include <raylib.h>
#include <iostream>
#include "../headers/entities.h"

void DrawTextureComponents(entt::registry& registry);
bool SetTexture(Texture2D* texture, std::string path);