local Button = {}

function Button:Start()
end

function Button:Update()
    local clicked = GetComponentValues(self.ID, "ButtonComponent")

    if clicked then
        
    end
end

return Button