local Drone = {}
Drone.hp = 3

function Drone:Start()
    self.shootTimer = coroutine.create(coShootBullet)
end

function Drone:Update()
    local move = ReadMoveComponent(self.ID)
    local shootCoolDown = 1
    coroutine.resume(self.shootTimer, shootCoolDown, true, "Drone", "ENEMYBULLET", move.xPos + 85, move.yPos)
end

function Drone:OnCollision(otherTag)
    if otherTag ~= "PLAYER" then
        self.hp = self.hp - 1

        if self.hp <= 0 then
            DeleteEntity(self.ID)
        end
    end
end

return Drone