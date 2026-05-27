
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
    AddGameSystemComponent(bullet, "game/lua/bullet.lua")
    AddBoxColliderComponent(bullet, posX, posY, 30, 80)
    AddCustomComponent(bullet, "GameTag", tag)

    local texturePath = "game/assets/textures/playerShot.png"
    if type == "Standard" then
        -- self.type = "Standard"
        -- self.damage = 6
        AddMoveComponent(bullet, posX, posY, 0, -10, 0)
    end

    if type == "SomethingElse" then
        -- self.type = "SomethingElse"
        -- self.damage = 9999
        texturePath = "ja"
        AddMoveComponent(bullet, posX, posY, 2, -10, 0)
    end

    AddTextureComponent(bullet, texturePath, posX, posY, 80, 50)
    
    return bullet
end
            

function CreatePlayer(posX, posY)
    player = CreateEntity()
    AddGameSystemComponent(player, "game/lua/player.lua")
    AddMoveComponent(player, posX, posY, 0, 0, 0) --speed doesn't matter here
    AddTextureComponent(player, "game/assets/textures/spaceship.png", posX, posY, 250, 250)
    AddInputComponent(player)
    AddTimerComponent(player, 0.5)
    AddBoxColliderComponent(player, posX, posY, 160, 80)
    AddCustomComponent(player, "GameTag", "PLAYER")

    return player
end

function CreateEnemyDrone(posX, posY)
    drone = CreateEntity()
    AddGameSystemComponent(drone, "game/lua/drone.lua")
    AddMoveComponent(drone, posX, posY, 0, 1, 0)
    AddTextureComponent(drone, "game/assets/textures/enemyDrone.png", posX, posY, 220, 220)
    AddBoxColliderComponent(drone, posX + 80, posY, 140, 140)
    AddCustomComponent(drone, "GameTag", "ENEMY")

    return drone
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

