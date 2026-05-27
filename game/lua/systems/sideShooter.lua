local SideShooter = {}
SideShooter.hp = 12

function SideShooter:Start()
    print("Spawned sideShooter")
    self.shootTimer = coroutine.create(coShootBullet)
    self.canShoot = false
    self.canShootTimer = 1.5
end

function SideShooter:Update()
    local move = ReadMoveComponent(self.ID)
    local shootCoolDown = 3

    if sideShooterOffsetMap[self.ID] == 2 then
        self.canShootTimer = self.canShootTimer - GetDeltaTime()

        if self.canShootTimer <= 0 then
            self.canShoot = true
        end

    else
        self.canShoot = true
    end

    coroutine.resume(self.shootTimer, shootCoolDown, self.canShoot, "SideShooter", "ENEMYBULLET", move.xPos + 85, move.yPos + 100)
end

function SideShooter:OnCollision(otherTag)
    if otherTag ~= "ENEMYBULLET" and otherTag ~= "ENEMY" then
        self.hp = self.hp - 1
    end

    if self.hp <= 0 or otherTag == "PLAYER" then
        DeleteEntity(self.ID)
    end
end

return SideShooter