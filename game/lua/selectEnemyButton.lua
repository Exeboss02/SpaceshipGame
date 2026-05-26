currentIndex = 0

local Button = {}

function Button:Start()
    print("Spawned bullet")
end

function Button:Update()
    local clicked = GetComponentValues(self.ID, "ButtonComponent")

    if clicked then
        currentIndex = currentIndex + 1
        if currentIndex > 3 then
            currentIndex = 0
        end

        if(currentIndex == 0) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/enemyDrone.png")
        end

        if(currentIndex == 1) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/enemyShotgun.png")
        end

        if(currentIndex == 2) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/enemySideShooter.png")
        end

        if(currentIndex == 3) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/white.png")
        end
    end
end

return Button