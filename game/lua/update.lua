
function PlayerUpdate()
    local playerSpeed = 160.0
    local input = {}
    input = ReadInput(player) --player is a global entity
    totalInput = input["xInput"] + input["yInput"]

    if totalInput > 1 then
        input["xInput"] = 1 / (input["xInput"] + input["yInput"])
        input["yInput"] = 1 / (input["xInput"] + input["yInput"])
    end

    deltaTime = GetDeltaTime()
    SetMoveComponentVelocity(player, input["xInput"] * playerSpeed * deltaTime, input["yInput"] * playerSpeed * deltaTime)
end

PlayerUpdate()
