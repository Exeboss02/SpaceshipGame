local SideShooter = {}
SideShooter.hp = 10

function SideShooter:Start()
    print("Spawned drone")
end

function SideShooter:Update()
    --set velocity etc
end

function SideShooter:OnCollision(otherTag)
    if otherTag ~= "PLAYER" then
        self.hp = self.hp - 1

        if self.hp <= 0 then
            DeleteEntity(self.ID)
        end
    end
end

return SideShooter