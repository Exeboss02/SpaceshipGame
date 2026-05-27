CreateBackground("game/assets/textures/space3.png", 150.0)

local spawnData = ReadFile(currentSelectedLevel) --global value in levelEditing.lua
spawnData = spawnData:gsub("\n", "")
local blockSize = 35
local nrOfBlocks = #spawnData / blockSize

--------------------------------------------------------------------------

sideShooterOffsetMap = {}
sideShooterOffsetValue = 1

function coSpawner()
    --spawn in grid
    local block = 1
    local blockSpawnTimer = 2

    while block < nrOfBlocks + 1 do
        blockSpawnTimer = blockSpawnTimer - GetDeltaTime()
        coroutine.yield()

        if blockSpawnTimer <= 0 then
            for col=1, 7 do --row major loop instead of previous column major
                for row=1, 5 do
                    local index = (block - 1) * 35 + (row - 1) * 7 + col
                    local char = spawnData:sub(index, index)
                    if char == "0" then
                        CreateEnemyDrone(424 * row - 400, -190 * (8 - col) - 50)
                    end

                    if char == "1" then
                        CreateEnemyShotgun(424 * row - 400, -190 * (8 - col) - 50)
                    end

                    if char == "2" then
                        sideShooter = CreateEnemySideShooter(424 * row - 400, -190 * (8 - col) - 50)
                        sideShooterOffsetMap[sideShooter] = sideShooterOffsetValue
                        sideShooterOffsetValue = sideShooterOffsetValue + 1

                        if sideShooterOffsetValue > 2 then
                            sideShooterOffsetValue = 1
                        end
                    end
                end
            end

            block = block + 1
            blockSpawnTimer = 6
        end
    end

    coroutine.close()
end

spawner = CreateEntity()
AddGameSystemComponent(spawner, "game/lua/systems/enemySpawner.lua")

player = CreatePlayer(850, 700)

CreateButton(20, 30, 80, 50, "game/assets/textures/mainMenu.png", "game/lua/buttons/startScreenButton.lua")