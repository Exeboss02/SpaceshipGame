#pragma once

#include "../headers/entities.h"

lua_State* LuaSetup();

int lua_ReferenceAndPushBehaviour(lua_State* L);
int lua_CreateEntity(lua_State* L);
int lua_AddMoveComponent(lua_State* L);
int lua_AddTextureComponent(lua_State* L);
int lua_AddInputComponent(lua_State* L);
int lua_AddTimerComponent(lua_State* L);
int lua_AddBoxColliderComponent(lua_State* L);
int lua_AddGameSystemComponent(lua_State* L);
int lua_AddCustomComponent(lua_State* L);

int lua_GetDeltaTime(lua_State* L);
int lua_GetComponentValues(lua_State* L); //retrieve in lua
int lua_SetComponentValues(lua_State* L);

int lua_DeleteEntity(lua_State* L);