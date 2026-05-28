local Bullet = {}
Bullet.type = "Standard"
Bullet.timeLeft = 3

function Bullet:Start()
    print("Spawned bullet")
end

function Bullet:Update()
    self.timeLeft = self.timeLeft - GetDeltaTime()
    if(self.timeLeft <= 0) then
        DeleteEntity(self.ID)
    end
end

function Bullet:OnCollision(otherTag)
    if (bulletTagMap[self.ID] == "ENEMYBULLET" and otherTag == "PLAYER") or (bulletTagMap[self.ID] == "PLAYERBULLET" and otherTag == "ENEMY") then
        DeleteEntity(self.ID)
    end
end

return Bullet