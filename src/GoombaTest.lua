local MovementSpeed = 50
local PatrollingBehaviours = {}

function Patrol(host, patrolWaypointOne, patrolWaypointTwo, ID)
    while true do
        _PatrolToPoint(host, patrolWaypointOne, MovementSpeed, ID)
        coroutine.yield()
        _PatrolToPoint(host, patrolWaypointTwo, MovementSpeed, ID)
        coroutine.yield()
    end
end

function OnStart(host, spawnX, spawnY, patrolWaypointOne, patrolWaypointTwo, ID)
    PatrollingBehaviours[ID] = coroutine.create(Patrol)
end