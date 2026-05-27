local success, creatables = pcall(dofile, "game/lua/gameEntities.lua")
if not success then
    print("Error loading file")
    return
end

logo = CreateEntity()
AddTextureComponent(logo, "game/assets/textures/spaceGameLogo.png", 1100, 100, 700, 400)

CreateBackground("game/assets/textures/space.png", 80.0)

CreateButton(100, 100, 400, 200, "game/assets/textures/levelSelect.png", "game/lua/buttons/levelButton.lua") --level select button
CreateButton(100, 340, 400, 200, "game/assets/textures/levelEditing.png", "game/lua/buttons/editorButton.lua") --level editing button
