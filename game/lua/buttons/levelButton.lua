local Button = {}

function Button:Start()
    print("Spawned bullet")
end

function Button:Update()
    local clicked = GetComponentValues(self.ID, "ButtonComponent")

    if clicked then
        DeleteAllEntities()
        pcall(dofile, "game/lua/levels/level.lua")
    end
end

return Button