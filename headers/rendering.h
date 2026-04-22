#pragma once
#include <raylib.h>
#include <iostream>
#include "../headers/entities.h"

void DrawTextureComponents(entt::registry& registry);
void SetTexture(Texture2D* texture, std::string path);