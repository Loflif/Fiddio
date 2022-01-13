local MovementSpeed = 50

Goombas = {}

function Patrol(deltaTime)
	while true do
			while _positionX < _leftWaypoint do
				_positionX = _positionX + (_currentSpeed * deltaTime)
				coroutine.yield()
			end
			_currentSpeed = _currentSpeed * -1
			while _positionX > _rightWaypoint do
				_positionX = _positionX + (_currentSpeed * deltaTime)
				coroutine.yield()
			end
			_currentSpeed = _currentSpeed * -1
		end
	end

local function Goomba(spawnX, spawnY, leftWaypoint, rightWaypoint, id)
	local _id = id
	_positionX = positionX
	_positionY = positionY
	local _leftWaypoint = leftWaypoint
	local _rightWaypoint = rightWaypoint
	_currentPatrolRoutine = coroutine.create(Patrol)

	_currentSpeed = MovementSpeed

	return Goomba
end

function OnStart(host, spawnX, spawnY, patrolWaypointOne, patrolWaypointTwo, id)
	--print("[Lua]: OnStart was called with id: " .. id)
	local leftWaypoint
	local rightWaypoint

	if patrolWaypointOne > patrolWaypointTwo then
		leftWaypoint = patrolWaypointOne
		rightWaypoint = patrolWaypointTwo
	else
		rightWaypoint = patrolWaypointOne
		leftWaypoint = patrolWaypointTwo
	end

	Goombas[id] = Goomba(spawnX, spawnY, leftWaypoint, rightWaypoint, id)
	--{
	--	PositionX = spawnX,
	--	PositionY = spawnY,
	--	
	--	CurrentSpeed = MovementSpeed,
	--	
	--	LeftWaypoint = leftWaypoint,
	--	RightWaypoint = rightWaypoint,
	--	CurrentPatrolRoutine = coroutine.create(Patrol)
	--}
end

function OnUpdate(host, deltaTime, positionX, positionY, id)
	--print("[Lua]: OnUpdate was called with id: " .. id)
	Goombas[id]._positionX = positionX
	Goombas[id]._positionY = positionY

	coroutine.resume(Goombas[id]._currentPatrolRoutine, deltaTime)

	_SetPosition(host, Goombas[id]._positionX, Goombas[id]._positionY)
	_SetVelocity(host, Goombas[id]._currentSpeed, 0)
end
