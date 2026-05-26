local Button = {}
Button.currentYindex = 0

function Button:Start()
end

function Button:Update()
    local clicked = GetComponentValues(self.ID, "ButtonComponent")

    if clicked then
        newLayerUI = CreateEntity()
        AddTextureComponent(newLayerUI, "game/assets/textures/layer.png", 600, 50 + self.currentYindex, 150, 60) --layer ui
        self.currentYindex = self.currentYindex + 70
    end
end

return Button