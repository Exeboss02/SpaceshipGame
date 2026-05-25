local success, creatables = pcall(dofile, "game/lua/gameEntities.lua")
if not success then
    print("Error loading file")
    return
end

CreateBackground("game/assets/textures/space.png", 80.0)

CreateButton(100, 100, 400, 300, "game/assets/textures/nitwBridge.png", "game/lua/levelButton.lua")
