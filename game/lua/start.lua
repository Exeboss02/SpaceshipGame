local success, creatables = pcall(dofile, "game/lua/gameEntities.lua")
if not success then
    print("Error loading file")
    return
end

CreateBackground("game/assets/textures/space.png", 55.0)

player = CreatePlayer(20, 40)

CreateEnemyDrone(200, 40)
CreateEnemyDrone(300, 80)
CreateEnemyDrone(400, 120)
CreateEnemyDrone(500, 160)
CreateEnemyDrone(600, 200)
