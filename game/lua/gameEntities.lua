
function CreatePlayer(posX, posY)
    player = CreateEntity()
    AddMoveComponent(player, posX, posY, 0, 0, 125)
    AddTextureComponent(player, "game/assets/textures/HumanoidTpose.png", posX, posY, 150, 80)
    AddInputComponent(player)
    AddTimerComponent(player, 0.5)
    AddBoxColliderComponent(player, posX, posY, 160, 80)
    AddCustomComponent(player, "GameTag", "PLAYER")
    AddCustomComponent(player, "GunComponent", 0.01, 0.0)
end

function CreateEnemyDrone(posX, posY)
    drone = CreateEntity()
    AddMoveComponent(drone, posX, posY, 0, 0, 40.0)
    AddTextureComponent(drone, "game/assets/textures/nitwBridge.png", posX, posY, 120, 80)
    AddBoxColliderComponent(drone, posX, posY, 80, 50)
    AddCustomComponent(drone, "GameTag", "ENEMY")
    AddCustomComponent(drone, "GunComponent", 0.01, 0.0)
    AddCustomComponent(drone, "HealthComponent", 10.0)
end