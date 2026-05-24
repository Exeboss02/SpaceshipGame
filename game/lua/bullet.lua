local Bullet = {}
Bullet.type = "Standard"
Bullet.damage = 6

function Bullet:Start()
    print("Spawned bullet")
end

function Bullet:Update()
    --set velocity etc
end

function Bullet:OnCollision(otherTag)
    if otherTag ~= "PLAYER" then
        DeleteEntity(self.ID)
    end

    print(otherTag)
end

return Bullet