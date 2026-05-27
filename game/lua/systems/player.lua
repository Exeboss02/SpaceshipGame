local Player = {}
Player.hp = 3

function Player:Start()
    Player.tag = "Player"
    Player.shoot = false
    Player.shootTimer = coroutine.create(coShootBullet)
end

function Player:Update()
    local playerSpeed = 550.0
    local input = ReadInput(self.ID) --player is a global entity
    local move = ReadMoveComponent(self.ID)
    local totalInput = math.sqrt(input.xInput * input.xInput + input.yInput * input.yInput)

    if input.shift then
        playerSpeed = 200
    end

    shoot = input.shootButton
    shootCoolDown = 0.3
    coroutine.resume(self.shootTimer, shootCoolDown, shoot, "Standard", "PLAYERBULLET", move.xPos + 85, move.yPos)


    if totalInput > 1 then
        input.xInput = input.xInput / totalInput
        input.yInput = input.yInput / totalInput
    end

    deltaTime = GetDeltaTime()
    xVelocity = input.xInput * playerSpeed * deltaTime
    yVelocity = input.yInput * playerSpeed * deltaTime
    SetComponentValues(self.ID, "MoveComponent", move.xPos, move.yPos, xVelocity, yVelocity)
    --maybe setcomponent, in c++ registry.emplace_or_replace
end

function Player:OnCollision(otherTag)
    if otherTag == "ENEMYBULLET" then
        self.hp = self.hp -1
    end

    if otherTag == "ENEMY" then
        playerIsDead = true
        DeleteEntity(self.ID)
    end

        --reload scene function
end

return Player
