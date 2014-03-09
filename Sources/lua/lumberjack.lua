function Lumberjack:action()
--[[
	if self:isAttacked() then
		local entities = self:getEntities()
		local i = 1
		local size = entities:getSize()
		while (i <= size) and (not ((entities:*agressif*(i)) and (entities:getDistance(i) == 1))) do
			i=i+1
		end
		if i > size then
			return “move”
		end
		
		self:setAngle(entities:getAngle(i))
		return “attack”

	elseif self:fullBag() then
		if self:isNearHome() then
			return “give”
		else
			return “gohome”
		end

	elseif self:emptyBag() then	
		if self:isNearResource() then
			return “take”
		elseif self:getNearestResource() then
			return “gonearest”

		else
			if self:isNearHome() then
				self:setAngle((self:getAngle()+180)%360)
			end
			return “move”
		end
	end
]]
	return "move"
end
