local Drone = {}
Drone.hp = 3

function Drone:Start()
    print("Spawned drone")
end

function Drone:Update()
    --set velocity etc
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