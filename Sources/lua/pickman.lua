--SCRIPT MINEUR

function Pickman:action()

	if self:getHealth()==WEAK then
		local entities = self:getEntities()
		local size = entities:getSize()
		local angle=0
		local nb=0
		for i=1, size, 1 do
			if (entities:getType(i)==WILD_ANIMAL) or (entities:getType(i)==ENEMY_CITIZEN) then
				angle= angle + entities:getAngle(i)
				nb=nb + 1
			end
		end
		if nb~=0 then
			angle= angle / nb
			self:setAngle((angle + math.pi)%2*math.pi)
			return "move"
		end
	elseif self:isAttacked() then
		local entities = self:getEntities()
		local size = entities:getSize()
		local i = 1
		local statement = true
		local target = 0
		while (i<=size) and statement do
			if self:isAttackMe(entities:getID(i)) then
				if entities:getAngle(i)==self:getAngle() then
					target = i
					statement = false
				elseif target == 0 then
					target = i
				end
			end
			i = i + 1
		end
		if target == 0 then
			print("! WARNING ! pickman.lua : recherche de cible")
		else
			self:setTarget(entities:getID(target))
			return "attack"
		end
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
			local rand = self:getRandom()%3
			if rand == 1 then
				self:setAngle((self:getAngle()-(math.pi/4))%2*math.pi)
			elseif rand == 2 then
				self:setAngle((self:getAngle()+(math.pi/4))%2*math.pi)
			end
			return "move"
		end
	end
end
