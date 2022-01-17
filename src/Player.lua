Acceleration = 500
Deceleration = 600
MaxMoveSpeed = 300
Gravity = 3000
FallingGravity = 5000
JumpForce = 900
BounceForce = 500

function OnStart(host)

end

function OnUpdate(host, deltaTime, velocityX, velocityY, movementInput)
	local frameVelocityX = velocityX
	local frameVelocityY = velocityY

	frameVelocityY = AddGravity(deltaTime, frameVelocityY)

	if movementInput == 0 then
		frameVelocityX = Decelerate(deltaTime, frameVelocityX)
	else 
		frameVelocityX = Accelerate(deltaTime, frameVelocityX, movementInput)
	end
	_SetVelocity(host, frameVelocityX, frameVelocityY)
end

function AddGravity(deltaTime, velocityY)
	if velocityY > 0 then
		velocityY = velocityY + (FallingGravity * deltaTime)
	else
		velocityY = velocityY + (Gravity * deltaTime)
	end
	
	return velocityY
end

function OnJump(host, velocityY)
	velocityY = velocityY - JumpForce
	_SetVelocityY(host, velocityY)
end

function OnBounce(host)
	velocityY = - BounceForce
	_SetVelocityY(host, velocityY)
end


function Decelerate(deltaTime, velocityX)
	potentialDeceleration = Deceleration * deltaTime	

	if velocityX > potentialDeceleration then
		velocityX = velocityX - potentialDeceleration
	elseif velocityX < -potentialDeceleration then
		velocityX = velocityX + potentialDeceleration
	else
		velocityX = 0
	end
	return velocityX
end

function Accelerate(deltaTime, velocityX, movementInput)
	if movementInput == 1 then
		if velocityX < MaxMoveSpeed then
			velocityX = velocityX + (Acceleration * deltaTime)
		else
			velocityX = MaxMoveSpeed
		end
	else
		if velocityX > -MaxMoveSpeed then
			velocityX = velocityX - (Acceleration * deltaTime)
		else
			velocityX = -MaxMoveSpeed
		end
	end
	return velocityX
end