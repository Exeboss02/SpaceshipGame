local Button = {}

function Button:Start()
    print("Spawned bullet")
end

function Button:Update()
    local clicked = GetComponentValues(self.ID, "ButtonComponent")
    print(clicked)

    if clicked then
        print("HEJ----------------------------------------------------------")
        CreateEnemyDrone(300, 80)
    end
end

return Button