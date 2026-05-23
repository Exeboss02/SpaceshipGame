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

int lua_GetInputValues(lua_State* L);
int lua_GetDeltaTime(lua_State* L);

int lua_SetMoveComponentVelocity(lua_State* L);
int lua_SetTextureComponent(lua_State* L);
int lua_SetInputComponent(lua_State* L);
int lua_SetTimerComponent(lua_State* L);
int lua_SetBoxColliderComponent(lua_State* L);