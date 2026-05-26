#pragma once
#include <string>
#include "../../headers/entities.h"

void DrawBackground(entt::registry& registry);

int lua_AddCustomComponent(lua_State *L);
int lua_ReadFile(lua_State* L);
int lua_WriteToFile(lua_State* L);
int lua_ClearFile(lua_State* L);

template<typename T, typename... Args>
void AddCustomComponent(entt::registry& registry, entt::entity entity, Args&&... args);