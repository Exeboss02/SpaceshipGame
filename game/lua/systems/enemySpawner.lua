local Spawner = {}
playerIsDead = false --global flag
restartTimer = 2

function Spawner:Start()
    self.coSpawner = coroutine.create(coSpawner)
end

function Spawner:Update()
    coroutine.resume(self.coSpawner)

    if playerIsDead then
        restartTimer = restartTimer - GetDeltaTime()

        if restartTimer <= 0 then
            DeleteAllEntities()
            pcall(dofile, "game/lua/levels/start.lua")
        end
    end
end

function Spawner:OnCollision(otherTag)
end

return Spawner