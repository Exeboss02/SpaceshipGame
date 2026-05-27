local Button = {}

function Button:Start()
end

function Button:Update()
    local clicked = GetComponentValues(self.ID, "ButtonComponent")
    local index = idIndexMap[self.ID]

    if clicked then
        if(currentEnemyIndex == 0) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/enemyDrone.png")
            waveString[index] = "0"

            print("self.ID: " .. self.ID)
            print("mapIndex: " .. index)
        end

        if(currentEnemyIndex == 1) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/enemyShotgun.png")
            waveString[index] = "1"
        end

        if(currentEnemyIndex == 2) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/enemySideShooter.png")
            waveString[index] = "2"
        end

        if(currentEnemyIndex == 3) then
            SetComponentValues(self.ID, "TextureComponent", "game/assets/textures/white.png")
            waveString[index] = "3"
        end
    end
end

return Button