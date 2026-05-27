local Shotgun = {}
Shotgun.hp = 3

function Shotgun:Start()
    print("Spawned shotgun")
    self.shootTimer = coroutine.create(coShootBullet)
end

function Shotgun:Update()
    local move = ReadMoveComponent(self.ID)
    local shootCoolDown = 1.5
    coroutine.resume(self.shootTimer, shootCoolDown, true, "Shotgun", "ENEMYBULLET", move.xPos + 85, move.yPos + 100)
end

function Shotgun:OnCollision(otherTag)
    if otherTag ~= "ENEMYBULLET" and otherTag ~= "ENEMY" then
        self.hp = self.hp - 1

        if self.hp <= 0 or otherTag == "PLAYER" then
            DeleteEntity(self.ID)
        end
    end
end

return Shotgun