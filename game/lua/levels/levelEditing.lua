CreateButton(20, 30, 80, 50, "game/assets/textures/nitwBridge.png", "game/lua/startScreenButton.lua") --exit button

--the grid with buttons
for i=0, 4 do
    for j=0, 6 do
        CreateButton(1000 + i * 70 + i * 10, 250 + j * 70 + j * 10, 70, 70, "game/assets/textures/white.png", "game/lua/editorButton.lua")
    end
end

--select enemy buttons and add button
for i=0, 3 do
    local texture = "game/assets/textures/enemyDrone.png"
    local script = "game/lua/selectEnemyButton.lua"

    if i == 3 then
        script = "game/lua/addButton.lua"
        texture = "game/assets/textures/add.png"
    end

    CreateButton(900, 490 + i * 70 + i * 10, 70, 70, texture, script)
end

background1 = CreateEntity()
AddTextureComponent(background1, "game/assets/textures/blue.png", 880, 230, 530, 600) --grid background

CreateBackground("game/assets/textures/space3.png", 9.0) --scene background