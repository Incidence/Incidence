--SCRIPT BUCHERON

function Lumberjack:action()

local driftAngle=35
	
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
			self:setAngle(angle+math.pi)
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
			math.randomseed(os.time())
			math.random()
			math.random()
			local rand = math.floor(math.random()*10000)%5
			print(rand)
			if rand == 0 then
				self:setAngle(self:getAngle()-math.pi/2)
				return "move"
			elseif rand == 4 then
				self:setAngle(self:getAngle()+math.pi/2)
				return "move"
			else
				self:setAngle(self:getAngle())
				return "move"
			end
		return "move"
		end
	end
end
