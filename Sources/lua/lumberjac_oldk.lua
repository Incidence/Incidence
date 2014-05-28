--SCRIPT BUCHERON

function Lumberjack:action()
	
	if self:getHealth()=="WEAK" then
		local entities = self:getEntities()
		local size = entities:getSize()
		local angle=0
		local nb=0
		for i=1, size, 1 do
			if (entities:getType(i)=="WILD_ANIMAL") or (entities:getType(i)=="ENEMY_CITIZEN") then
				angle= angle + entities:getAngle(i)
				nb=nb + 1
			end
		end
		if nb~=0 then
			angle= angle / nb
			self:setAngle((angle+180)%360)
			return "move"
		end
		--[[
	elseif self:isAttacked() then
		local entities = self:getEntities()
		local size = entities:getSize()
		local target=0
		for i=1, size, 1  do
			if ((entities:getType(i)=="WILD_ANIMAL") or (entities:getType(i)=="ENEMY_CITIZEN")) and (self:nearEntity(i)) then
				if target==0 then
					target=i
				elseif entities:getHealth(i)<entities:getHealth(target) then
					target=i
				elseif entities:getHealth(i)==entities:getHealth(target) and entities:getAngle(i)==self:getAngle() then
					target=i
				end
			end
		end
		self:setTarget(target)
		return "attack"
		]]--
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
			if self:isNearHome() then
				self:setAngle((self:getAngle()+180)%360)
			end
			return "move"
	end
end
end
