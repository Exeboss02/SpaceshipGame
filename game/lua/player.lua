-- function coShooting(deltaTime)

local Player = {}

function Player:Start()
    print("THE PLAYER HAS STARTED DOING STUFF, NOOOOOOOOO!")
end

function Player:Update()
    local playerSpeed = 160.0
    local input = ReadInput(self.ID) --player is a global entity
    local totalInput = input.xInput + input.yInput

    if totalInput > 1 then
        input.xInput = 1 / (input.xInput + input.yInput)
        input.yInput = 1 / (input.xInput + input.yInput)
    end

    deltaTime = GetDeltaTime()
    xVelocity = input.xInput * playerSpeed * deltaTime
    yVelocity = input.yInput * playerSpeed * deltaTime
    SetMoveComponentVelocity(self.ID, xVelocity, yVelocity)
    --maybe setcomponent, in c++ registry.emplace_or_replace

    if input.shootButton then
        CreateBullet("Standard", 200, 200)
    end
end

return Player
