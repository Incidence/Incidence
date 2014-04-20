--SCRIPT WILD_ANIMAL

function WildAnimal:action()

	local entities = self:getEntities()
	local size = entities:getSize()
	local i = 1
	local statement = true
	local target = 0
	while (i<=size) and statement do
		if entities:getType(i)~=WILD_ANIMAL then
			if entities:getAngle(i)==self:getAngle() then
				target = i
				statement = false
			elseif target == 0 then
				target = i
			end
		end
		i = i + 1
	end
	if target ~= 0 then
		self:setTarget(entities:getID(target))
		return "attack"
	else
		math.randomseed(os.time())
		math.random()
		math.random()
		local rand = math.floor(math.random()*10000)%5
		if rand == 0 then
			self:setAngle((self:getAngle()-(math.pi/4))%2*math.pi)
		elseif rand == 4 then
			self:setAngle((self:getAngle()+(math.pi/4))%2*math.pi)
		end
		return "move"
	end
end
