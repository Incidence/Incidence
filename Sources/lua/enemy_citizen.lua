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

		while (i<=taille) do -- priorité aux citoyens risque de tout parcourir(sinon on fait un || entre animaux agressifs  et citoyens.
			if (self:isAttackMe(entites:getID(i))) and (entites:getAngle(i)==self:getAngle()) then
				indice=i

			elseif (not((self:isAttackMe(entites:getID(indice))) and (entites:getAngle(indice)==self:getAngle()))) then
				if (self:isAttackMe(entites:getID(i))) and (entites:getType(i)==HUNTER) then
					indice=i
				elseif (not(self:isAttackMe(entites:getID(indice)) and entites:getType(indice)==HUNTER)) then
					if (self:isAttackMe(entites:getID(i))) and (entites:getType(i)==ALLY_CITIZEN) then
						indice=i
					elseif (not(self:isAttackMe(entites:getID(indice)) and entites:getType(indice)==ALLY_CITIZEN)) then
						if (self:getDistance(entites:getID(i))==1) and (entites:getType(i)==HUNTER) then
							indice=i
						elseif (not((self:getDistance(entites:getID(indice))==1) and (entites:getType(indice)==HUNTER))) then
							if	(entites:getType(i)==ALLY_CITIZEN) and (self:getDistance(entites:getID(i))==1) then
								indice=i
							elseif (not((entites:getType(indice)==ALLY_CITIZEN) and (self:getDistance(entites:getID(indice))==1))) then
								if (entites:getType(i)==WILD_ANIMAL) and (self:isAttackMe(entites:getID(i))) then
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
				self:setTarget(entites:getID(indice))
				return "attack"
			else
				local moyangle=sumangle/nbfoes
				self:setAngle(moyangle+math.pi)
				return "move"
			end

	else
		local sumangle=0
		while (i<=taille) do

			if entites:getType(i)==HUNTER then --Chasseur � nous
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
				if (not ((entites:getType(indice)==WILD_ANIMAL) or (entites:getType(indice)==PEACEFUL_ANIMAL) or (entites:getType(indice)==ENEMY_CITIZEN) )) then
					self:setTarget(entites:getID(indice))
					--print("ennemi")
					return "attack"
				else
				local rand = self:getRandom()%3
				if rand == 1 then
					self:setAngle((self:getAngle()-(math.pi/4))%2*math.pi)
				elseif rand == 2 then
					self:setAngle((self:getAngle()+(math.pi/4))%2*math.pi)
				end
				return "move"
				end
			else
				local moyangle=sumangle/nbfoes
				self:setAngle(moyangle+math.pi)
				return "move"
			end
		else
		--print("no perception")
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
