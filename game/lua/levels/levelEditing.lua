waveString = {}
idIndexMap = {}

local test = CreateButton(20, 30, 80, 50, "game/assets/textures/nitwBridge.png", "game/lua/startScreenButton.lua") --exit button
print(test)
print("END OF TEST----------------")

--the grid with buttons
for i=1, 5 do
    for j=1, 7 do
        local id = CreateButton(1000 + (i - 1) * 70 + (i - 1) * 10, 250 + (j - 1) * 70 + (j - 1) * 10, 70, 70, "game/assets/textures/white.png", "game/lua/enemyGridButton.lua")
        idIndexMap[id] = (i - 1) * 7 + j
    end
end

--initialize waveString
for i=1, 35 do
    waveString[i] = "3"
end

--select enemy buttons and add button
for i=0, 1 do
    local texture = "game/assets/textures/enemyDrone.png"
    local script = "game/lua/selectEnemyButton.lua"

    if i == 1 then
        script = "game/lua/addButton.lua"
        texture = "game/assets/textures/add.png"
    end

    CreateButton(900, 650 + i * 70 + i * 10, 70, 70, texture, script)
end

background1 = CreateEntity()
AddTextureComponent(background1, "game/assets/textures/blue.png", 880, 230, 530, 600) --grid background

CreateBackground("game/assets/textures/space3.png", 9.0) --scene background