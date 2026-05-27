local Drone = {}
Drone.hp = 3

function Drone:Start()
    print("Spawned drone")
end

function Drone:Update()
end

function Drone:OnCollision(otherTag)
    if otherTag ~= "ENEMYBULLET" then
        self.hp = self.hp - 1

        if self.hp <= 0 or otherTag == "PLAYER" then
            DeleteEntity(self.ID)
        end
    end
end

return Drone