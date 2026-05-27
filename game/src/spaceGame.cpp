#include "../game/headers/spaceGame.h"

template<typename T, typename... Args>
void AddCustomComponent(entt::registry& registry, entt::entity entity, Args&&... args)
{
    registry.emplace<T>(entity, std::forward<Args>(args)...);
}

int lua_AddCustomComponent(lua_State *L)
{
    entt::registry& registry = GetRegistry();
    entt::entity entity = static_cast<entt::entity>(lua_tointeger(L, 1));
    std::string type = lua_tostring(L, 2);

    //do I really need to return values > 0 here?

    if(type == ("BackgroundComponent"))
    {
        float scrollSpeed = static_cast<float>(lua_tonumber(L, 3));

        AddCustomComponent<BackgroundComponent>(registry, entity, scrollSpeed);
        return 3;
    }

    else if(type == ("GameTag"))
    {
        std::string tag = static_cast<std::string>(lua_tostring(L, 3));
        AddCustomComponent<std::string>(registry, entity, tag);

        return 0;
    }

    return 0;
}

int lua_ReadFile(lua_State *L)
{
    std::string filePath = static_cast<std::string>(lua_tostring(L, 1));
    std::ifstream file(filePath);
    std::string data = "";
    std::string row = "";

    while (std::getline(file, row))
    {
        data += row;
    }

    lua_pushstring(L, data.c_str());

    return 1;
}

int lua_WriteToFile(lua_State *L)
{
    std::string filePath = static_cast<std::string>(lua_tostring(L, 1));
    std::string data = static_cast<std::string>(lua_tostring(L, 2));

    std::ofstream spawnFile(filePath, std::ios::app);

    if (!spawnFile.is_open())
    {
        std::cout << "Error: Could not open file at " << filePath << std::endl;
        return 0;
    }
    
    spawnFile << data;
    spawnFile.close();

    return 0;
}

int lua_ClearFile(lua_State *L)
{
    std::string filePath = static_cast<std::string>(lua_tostring(L, 1));

    std::ofstream spawnFile(filePath);
    spawnFile << "";
    spawnFile.close();

    return 0;
}

void DrawBackground(entt::registry &registry)
{
    float deltaTime = GetFrameTime();
    static float offsetY = 0;

    auto view = registry.view<TextureComponent, BackgroundComponent>();
    for (auto [entity, textureComponent, backgroundComponent] : view.each())
    {
        textureComponent.textureContainer->texture.width = textureComponent.size.x;
        textureComponent.textureContainer->texture.height = textureComponent.size.y;

        offsetY += backgroundComponent.scrollSpeed * deltaTime;
        if(offsetY >= textureComponent.size.y)
        {
            offsetY = 0;
        }

        DrawTextureEx(textureComponent.textureContainer->texture, Vector2{0, offsetY}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(textureComponent.textureContainer->texture, Vector2{0, offsetY - textureComponent.size.y}, 0.0f, 1.0f, WHITE);
    }
}
