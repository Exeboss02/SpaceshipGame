CreateBackground("game/assets/textures/space3.png", 55.0)

local spawnData = ReadFile("game/lua/levels/spawn1.flerp")
spawnData = spawnData:gsub("\n", "")
local blockSize = 35
local nrOfBlocks = #spawnData / blockSize

print("NROFBLOCKS-----------")
print(nrOfBlocks)
print("NROFBLOCKS-----------")

--spawn in grid
for block=1, nrOfBlocks do
    for col=1, 7 do --row major loop instead of previous column major
        for row=1, 5 do
            local index = (block - 1) * 35 + (row - 1) * 7 + col
            local char = spawnData:sub(index, index)
            if char == "0" then
                CreateEnemyDrone(424 * row - 400, -190 * (8 - col) - 50 - (block - 1) * 1400)
            end
        end
    end
end


player = CreatePlayer(20, 40)

CreateButton(20, 30, 80, 50, "game/assets/textures/nitwBridge.png", "game/lua/startScreenButton.lua")