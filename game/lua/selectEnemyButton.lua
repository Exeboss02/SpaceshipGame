currentEnemyIndex = 0

local Button = {}

function Button:Start()
    print("Spawned bullet")
end

function Button:Update()
    local clicked = GetComponentValues(self.ID, "ButtonComponent")

    if clicked then
        currentEnemyIndex = currentEnemyIndex + 1
        if currentEnemyIndex > 3 then
            currentEnemyIndex = 0
        end

        if(currentEnemyIndex == 0) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/enemyDrone.png")
        end

        if(currentEnemyIndex == 1) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/enemyShotgun.png")
        end

        if(currentEnemyIndex == 2) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/enemySideShooter.png")
        end

        if(currentEnemyIndex == 3) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/white.png")
        end
    end
end

return Button