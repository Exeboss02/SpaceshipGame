#include "../headers/rendering.h"

void DrawTextureComponents(entt::registry& registry)
{
    auto view = registry.view<TextureComponent>();
    for (auto [entity, textureComponent] : view.each())
    {
        DrawTextureV(textureComponent.texture, {textureComponent.position}, WHITE);
    }
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