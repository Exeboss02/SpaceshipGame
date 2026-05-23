#pragma once
#include "../../headers/entities.h"

void DrawBackground(entt::registry& registry);

template<typename T, typename... Args>
void AddCustomComponent(entt::registry& registry, entt::entity entity, Args&&... args);