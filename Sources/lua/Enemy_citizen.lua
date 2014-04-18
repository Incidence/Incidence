--Script citoyen ennemi


function EnemyCitizen:action()

	local entites=self:getEntities()
	local taille=entites:getSize()
	local i=1
	local indice=1
	local nbfoes=0
	local nbfriends=0

	if self:isAttacked() then

		local sumangle=0
		while (i<=taille) do -- prioritÃ© aux citoyens risque de tout parcourir(sinon on fait un || entre animaux agressifs  et citoyens.

			if (entites:isAttackMe(entites:getID(i))) and (entites:getAngle(i)==self:getAngle()) then
				indice=i

			elseif (not((entites:isAttackMe(entites:getID(indice))) and (entites:getAngle(indice)==self:getAngle()))) then
				if (entites:isAttackMe(entites:getID(i))) and (entites:getType(i)==HUNTER) then
					indice=i

				elseif (not(entites:isAttackMe(entites:getID(indice)) and entites:getType(indice)==HUNTER)) then
					if (entites:isAttackMe(entites:getID(i))) and (entites:getType(i)==ALLY_CITIZEN) then
						indice=i

					elseif (not(entites:isAttackMe(entites:getID(indice)) and entites:getType(indice)==ALLY_CITIZEN)) then
						if (entites:getDistance(i)==1) and (entites:getType(i)==HUNTER) then
							indice=i

						elseif (not((entites:getDistance(indice)==1) and (entites:getType(indice)==HUNTER))) then
							if	(entites:getType(i)==ALLY_CITIZEN) and (entites:getDistance(i)==1) then
								indice=i

							elseif (not((entites:getType(indice)==ALLY_CITIZEN) and (entites:getDistance(indice)==1))) then
								if (entites:getType(i)==WILD_ANIMAL) and (entites:isAttackme(i)) then
									indice=i
								end
							end
						end
					end
				end
			end

			if (entites:getType(i)== WILD_ANIMAL) or (entites:getType(i)==HUNTER) then
				nbfoes=nbfoes+1
				sumangle=sumangle+entites:getAngle(i)
			end

			if (entites:getType(i)== ENEMY_CITIZEN) then
				nbfriends=nbfriends+1
			end
			i=i+1
		end

		local seuil=nbfriends+2
		if(nbfoes<=seuil) then
			self:setTarget(entites:getId(indice))
			return "attack"
		else
			local moyangle=sumangle/nbfoes
			self:setAngle(moyangle+math.pi)
			return "move"
		end

	else
		local sumangle=0
		while (i<=taille) do

			if entites:getType(i)==HUNTER then --Chasseur à nous
				indice=i

			elseif (not(entites:getType(indice)==HUNTER)) then
				if entites:getType(i)==ALLY_CITIZEN then
					indice=i
				end
			end

			--[[elseif (not(entites:getType(indice)=="ALLY_CITIZEN")) then
					if (entites:getType(i)=="PACIFIC_CITIZEN") then
						indice=i
					end
				end]]-- pas d'ennemi neutre pour le moment

			if (entites:getType(i)== WILD_ANIMAL) or (entites:getType(i)==HUNTER) then
				nbfoes=nbfoes+1
				sumangle=sumangle+entites:getAngle(i)
			end

			if (entites:getType(i)== ENEMY_CITIZEN) then
				nbfriends=nbfriends+1
			end
			i=i+1
		end

		if(taille>0) then
			local seuil=nbfriends+2
			if(nbfoes<=seuil) then
				if (not ((entites:getType(indice)==WILD_ANIMAL) or (entites:getType(indice)==PEACEFUL_ANIMAL))) then
					self:setTarget(entites:getID(indice))
					return "attack"
				else
					math.randomseed(os.time())
					math.random()
					math.random()
					local rand = math.floor(math.random()*10000)%5
					--print(rand)
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
				end
			else
				local moyangle=sumangle/nbfoes
				self:setAngle(moyangle+math.pi)
				return "move"
			end
		else
			math.randomseed(os.time())
			math.random()
			math.random()
			local rand = math.floor(math.random()*10000)%5
			--print(rand)
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
		end
	end
end
