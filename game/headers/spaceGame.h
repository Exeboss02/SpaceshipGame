#pragma once
#include "../../headers/entities.h"

void DrawBackground(entt::registry& registry);

int lua_AddCustomComponent(lua_State *L);

template<typename T, typename... Args>
void AddCustomComponent(entt::registry& registry, entt::entity entity, Args&&... args);