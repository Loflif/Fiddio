local MovementSpeed = 50
local Goombas = {}

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

function Goomba(spawnX, spawnY, leftWaypoint, rightWaypoint, id)
	return 	
	{
		_id = id,
		_positionX = spawnX,
		_positionY = spawnY,
		_leftWaypoint = leftWaypoint,
		_rightWaypoint = rightWaypoint,

		_currentSpeed = MovementSpeed
	}
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
	Goombas[id]._behaviour = coroutine.create(Patrol)
	print(#Goombas)

end

function OnUpdate(host, deltaTime, positionX, positionY, id)
	print("[Lua]: OnUpdate was called with id: " .. id)
	--print(#Goombas)

	Goombas[id]._positionX = positionX
	Goombas[id]._positionY = positionY

	coroutine.resume(Goombas[id]._behaviour, deltaTime)

	_SetPosition(host, Goombas[id]._positionX, Goombas[id]._positionY)
	_SetVelocity(host, Goombas[id]._currentSpeed, 0)
end

--function SpawnGoomba(spawnX, spawnY, leftWaypoint, rightWaypoint, id)
--	Goombas[id] = Goomba(spawnX * 16, spawnY * 16, leftWaypoint * 16, rightWaypoint * 16)
--	Goombas[id]._behaviour = coroutine.create(Patrol)
--	print(#Goombas)
--end

--function SpawnGoombas()
--	id = 1
--	SpawnGoomba(18, 12, 1, 23, id) 
--	id = id + 1
--	SpawnGoomba(36, 12, 36, 44, id)
--	id = id + 1
--	SpawnGoomba(50, 12, 47, 44, id)
--	id = id + 1
--	SpawnGoomba(52, 12, 47, 44, id)
--	id = id + 1
--	SpawnGoomba(89, 4, 89, 96, id)
--	id = id + 1
--	SpawnGoomba(91, 4, 89, 96, id)
--	id = id + 1
--	SpawnGoomba(105, 12, 97, 140, id)
--	id = id + 1
--	SpawnGoomba(107, 12, 97, 140, id)
--	id = id + 1
--	SpawnGoomba(120, 12, 97, 140, id)
--	id = id + 1
--	SpawnGoomba(122, 12, 97, 140, id)
--	id = id + 1
--	SpawnGoomba(130, 12, 97, 140, id)
--	id = id + 1
--	SpawnGoomba(132, 12, 97, 140, id)
--	id = id + 1
--	SpawnGoomba(135, 12, 97, 140, id)
--	id = id + 1
--	SpawnGoomba(137, 12, 97, 140, id)
--	id = id + 1
--	SpawnGoomba(188, 12, 179, 193, id)
--	id = id + 1
--	SpawnGoomba(190, 12, 179, 193, id)
--
--	print(Goombas[12]._behaviour)
--end