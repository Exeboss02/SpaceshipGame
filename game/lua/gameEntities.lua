
function CreateBackground(texturePath, scrollSpeed)
    background = CreateEntity()
    AddTextureComponent(background, texturePath, 0, 0, 1920, 1080)
    AddCustomComponent(background, "BackgroundComponent", scrollSpeed)
end

function CreatePlayer(posX, posY)
    player = CreateEntity()
    AddMoveComponent(player, posX, posY, 0, 0, 0) --speed doesn't matter here
    AddTextureComponent(player, "game/assets/textures/HumanoidTpose.png", posX, posY, 150, 80)
    AddInputComponent(player)
    AddTimerComponent(player, 0.5)
    AddBoxColliderComponent(player, posX, posY, 160, 80)
    AddCustomComponent(player, "GameTag", "PLAYER")
    AddCustomComponent(player, "GunComponent", 0.01, 0.0)

    return player
end

function CreateEnemyDrone(posX, posY)
    drone = CreateEntity()
    AddMoveComponent(drone, posX, posY, 0, 0, 1040.0)
    AddTextureComponent(drone, "game/assets/textures/nitwBridge.png", posX, posY, 120, 80)
    AddBoxColliderComponent(drone, posX, posY, 80, 50)
    AddCustomComponent(drone, "GameTag", "ENEMY")
    AddCustomComponent(drone, "GunComponent", 0.01, 0.0)
    AddCustomComponent(drone, "HealthComponent", 10.0)

    return drone
end

--will probably not be used
function ReadInput(entity)
    local arrowUp, shootButton, xInput, yInput = GetInputValues(entity)

    table = {}
    table["arrowUp"] = arrowUp
    table["shootButton"] = shootButton
    table["xInput"] = xInput
    table["yInput"] = yInput

    return table
end

