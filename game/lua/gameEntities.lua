math.randomseed(os.time())

currentSelectedLevel = "game/lua/levels/spawn2.flerp"
currentEditingLevel = "game/lua/levels/spawn2.flerp"

bulletTagMap = {}

function CreateBackground(texturePath, scrollSpeed)
    background = CreateEntity()
    AddTextureComponent(background, texturePath, 0, 0, 1920, 1080)
    AddCustomComponent(background, "BackgroundComponent", scrollSpeed)
end

function CreateButton(xPos, yPos, sizeX, sizeY, texturePath, scriptPath)
    button = CreateEntity()
    AddButtonComponent(button)
    AddTextureComponent(button, texturePath, xPos, yPos, sizeX, sizeY)
    AddGameSystemComponent(button, scriptPath)

    return button
end

function CreateBullet(type, tag, posX, posY)
    bullet = CreateEntity()
    bulletTagMap[bullet] = tag
    AddGameSystemComponent(bullet, "game/lua/systems/bullet.lua")
    AddBoxColliderComponent(bullet, posX, posY, 30, 80)
    AddCustomComponent(bullet, "GameTag", tag)

    local texturePath = "game/assets/textures/playerShot.png"
    if type == "Standard" then
        AddMoveComponent(bullet, posX, posY, 0, -10, 0)
    end

    if type == "Shotgun" then
        texturePath = "game/assets/textures/playerShot.png"
        xValue = -1 + math.random() * 2
        AddMoveComponent(bullet, posX, posY + 50, xValue, 5, 0)
    end

    if type == "SideShooter" then
        texturePath = "game/assets/textures/playerShot.png"
        AddMoveComponent(bullet, posX, posY - 10, 1.5, 0, 0)
    end

    AddTextureComponent(bullet, texturePath, posX, posY, 80, 50)
    
    return bullet
end
            

function CreatePlayer(posX, posY)
    player = CreateEntity()
    AddGameSystemComponent(player, "game/lua/systems/player.lua")
    AddMoveComponent(player, posX, posY, 0, 0, 0) --speed doesn't matter here
    AddTextureComponent(player, "game/assets/textures/spaceship.png", posX, posY, 180, 180)
    AddInputComponent(player)
    AddTimerComponent(player, 0.5)
    AddBoxColliderComponent(player, posX, posY, 50, 70)
    AddCustomComponent(player, "GameTag", "PLAYER")

    return player
end

function CreateEnemyDrone(posX, posY)
    drone = CreateEntity()
    AddGameSystemComponent(drone, "game/lua/systems/drone.lua")

    xValue = -0.5 + math.random() * 1
    AddMoveComponent(drone, posX, posY, xValue, 5, 0)
    AddTextureComponent(drone, "game/assets/textures/enemyDrone.png", posX, posY, 220, 220)
    AddBoxColliderComponent(drone, posX + 80, posY, 120, 120)
    AddCustomComponent(drone, "GameTag", "ENEMY")

    return drone
end

function CreateEnemyShotgun(posX, posY)
    shotgun = CreateEntity()
    AddGameSystemComponent(shotgun, "game/lua/systems/shotgun.lua")
    AddMoveComponent(shotgun, posX, posY, 0, 2, 0)
    AddTextureComponent(shotgun, "game/assets/textures/enemyShotgun.png", posX, posY, 220, 220)
    AddBoxColliderComponent(shotgun, posX + 80, posY, 120, 120)
    AddCustomComponent(shotgun, "GameTag", "ENEMY")

    return shotgun
end

function CreateEnemySideShooter(posX, posY)
    sideShooter = CreateEntity()
    AddGameSystemComponent(sideShooter, "game/lua/systems/sideShooter.lua")
    AddMoveComponent(sideShooter, posX, posY, 0, 1, 0)
    AddTextureComponent(sideShooter, "game/assets/textures/enemySideShooter.png", posX, posY, 220, 220)
    AddBoxColliderComponent(sideShooter, posX + 80, posY, 120, 120)
    AddCustomComponent(sideShooter, "GameTag", "ENEMY")

    return sideShooter
end

function coShootBullet()
    local currentTime = 0

    while true do
        currentTime = currentTime - GetDeltaTime()

        local startTime, shoot, type, tag, xPos, yPos = coroutine.yield()

        if shoot and currentTime <= 0 then
            CreateBullet(type, tag, xPos, yPos)
            currentTime = startTime
        end
    end
end

function ReadInput(entity)
    local arrowUp, shootButton, shift, xInput, yInput = GetComponentValues(entity, "InputComponent")

    table = {}
    table.arrowUp = arrowUp
    table.shootButton = shootButton
    table.shift = shift
    table.xInput = xInput
    table.yInput = yInput

    return table
end

function ReadMoveComponent(entity)
    local xPos, yPos, xVel, yVel = GetComponentValues(entity, "MoveComponent")

    table = {}
    table.xPos = xPos
    table.yPos = yPos
    table.xVel = xVel
    table.yVel = yVel

    return table
end

