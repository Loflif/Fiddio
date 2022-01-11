Acceleration = 500
Deceleration = 600
MaxMoveSpeed = 300
Gravity = 2000
FallingGravity = 3000
JumpForce = 700

function OnStart(host)

end

function OnUpdate(host, deltaTime)
	--print("[LUA]: OnUpdate was called with deltaTime:" .. deltaTime)
end

function AddGravity(host, deltaTime, velocityY, falling)
	--print("[LUA]: AddGravity was called with deltaTime:" .. deltaTime)
	frameGravity = 0
	if falling then
		frameGravity = FallingGravity * deltaTime
	else
		frameGravity = Gravity * deltaTime
	end
	velocityY = velocityY + frameGravity
	_SetVelocityY(host, velocityY)
end

function OnJump(host, velocityY)
	--print("[LUA]: OnJump was called")
	velocityY = velocityY - JumpForce
	_SetVelocityY(host, velocityY)
end

function OnAccelerateRight(host, deltaTime, velocityX)
	--print("[LUA]: OnAccelerateRight was called")
	if velocityX < MaxMoveSpeed then
		velocityX = velocityX + (Acceleration * deltaTime)
	else
		velocityX = MaxMoveSpeed
	end
	
	_SetVelocityX(host, velocityX)
end

function OnAccelerateLeft(host, deltaTime, velocityX)
	--print("[LUA]: OnAccelerateLeft was called")
	if velocityX > -MaxMoveSpeed then
		velocityX = velocityX - (Acceleration * deltaTime)
	else
		velocityX = -MaxMoveSpeed
	end
	_SetVelocityX(host, velocityX)
end

function OnDecelerate(host, deltaTime, velocityX)
	potentialDeceleration = Deceleration * deltaTime	

	if velocityX > potentialDeceleration then
		velocityX = velocityX - potentialDeceleration
	elseif velocityX < -potentialDeceleration then
		velocityX = velocityX + potentialDeceleration
	else
		velocityX = 0
	end
	_SetVelocityX(host, velocityX)
end