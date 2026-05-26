local Button = {}
Button.currentYindex = 0

function Button:Start()
end

function Button:Update()
    local clicked = GetComponentValues(self.ID, "ButtonComponent")

    if clicked then
        waveString[36] = "\n"
        local data = table.concat(waveString)
        WriteToFile("game/lua/levels/spawn1.flerp", data)

        --create layer ui to indicate a write
        newLayerUI = CreateEntity()
        AddTextureComponent(newLayerUI, "game/assets/textures/layer.png", 600, 50 + self.currentYindex, 150, 60) --layer ui
        self.currentYindex = self.currentYindex + 70

        print("-------------FINAL STRING---------------")

        for i=1, 36 do
            print(waveString[i])
        end
    end
end

return Button