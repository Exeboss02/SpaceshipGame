local Button = {}

function Button:Start()
    print("Spawned bullet")
end

function Button:Update()
    local clicked = GetComponentValues(self.ID, "ButtonComponent")
    print(clicked)

    if clicked then
        DeleteAllEntities()
    end
end

return Button