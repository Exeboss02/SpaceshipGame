local Button = {}

function Button:Start()
    print("Spawned bullet")
end

function Button:Update()
    local clicked = GetComponentValues(self.ID, "ButtonComponent")

    if clicked then
        DeleteAllEntities()
        pcall(dofile, "game/lua/levels/start.lua")
    end
end

return Button