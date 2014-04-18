--SCRIPT CUEILLEUR

function Gatherer:action()

	local entities = self:getEntities()
	local size = entities:getSize()
	local angle = 0
	local nb = 0
	for i = 1,size,1 do
		if (entities:getType(i)==WILD_ANIMAL) or (entities:getType(i)==ENEMY_CITIZEN) then
			angle= angle + entities:getAngle(i)
			nb = nb + 1
		end
	end
	if nb ~= 0 then
		angle = angle / nb
		self:setAngle((angle + math.pi)%2*math.pi)
		return "move"
	elseif self:fullBag() then
		if self:isNearHome() then
			return "give"
		else
			return "gohome"
		end
	elseif self:emptyBag() then
		if self:isNearResource() then
			return "take"
		elseif self:getNearestResource() then
			return "gonearest"
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
end
