local Bullet = {}
Bullet.tag = "BULLET"
Bullet.type = "Standard"
Bullet.damage = 6

function Bullet:Start()
    print("Spawned bullet")
end

function Bullet:Update()
    --set velocity etc
end

function Bullet:OnCollision()
    print("Collision!")
end

return Bullet