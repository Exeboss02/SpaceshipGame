local Bullet = {}
Bullet.type = "Standard"
Bullet.timeLeft = 1

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
    if otherTag ~= "PLAYER" then
        DeleteEntity(self.ID)
    end

    print(otherTag)
end

return Bullet