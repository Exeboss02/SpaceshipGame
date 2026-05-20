local success, creatables = pcall(dofile, "game/lua/gameEntities.lua")
if not success then
    print("Error loading file")
    return
end

CreatePlayer(100, 40)
--CreateEnemyDrone(500, 40)
