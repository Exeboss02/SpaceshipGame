local Shotgun = {}
Shotgun.hp = 5

function Shotgun:Start()
    print("Spawned shotgun")
end

function Shotgun:Update()
    --set velocity etc
end

function Shotgun:OnCollision(otherTag)
    if otherTag ~= "PLAYER" then
        self.hp = self.hp - 1

        if self.hp <= 0 then
            DeleteEntity(self.ID)
        end
    end
end

return Shotgun