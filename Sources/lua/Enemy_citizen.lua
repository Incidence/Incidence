--Script citoyen ennemi


function Ennemy_citizen:action()

	local entites=self:getEntities()
	local taille=entites:getSize()
	local i=1
	local indice=1
	local nbfoes=0
	local nbfriends=0

	if self:isAttacked() then

		local sumangle=0
		while (i<=taille) do -- prioritÃ© aux citoyens risque de tout parcourir(sinon on fait un || entre animaux agressifs  et citoyens.

			if (entites:isAttackMe(i)) and (entites:getAngle(i)==self:getAngle()) then
				indice=i
				nbfoes=nbfoes+1
				sumangle=sumangle+entites:getAngle()

			elseif (not((entites:isAttackMe(indice)) and (entites:getAngle(indice)==self:getAngle()))) then
				if (entites:isAttackme(i)) and (entites:getType(i)=="ALLY_CITIZEN") then
					indice=i
					nbfoes=nbfoes+1
					sumangle=sumangle+entites:getAngle()

			elseif (not(entites:isAttackme(indice) and entites:getType(indice)=="ALLY_CITIZEN")) then
				if (entites:getType(i)=="ALLY_CITIZEN") and (entites:getDistance(i)==1) and (entites:getType(i)=="HUNTER") then
					indice=i
					nbfoes=nbfoes+1
					sumangle=sumangle+entites:getAngle()
				end

			elseif (not((entites:getType(indice)=="ALLY_CITIZEN") and (entites:getDistance(indice)==1) and (entites:getType(indice)=="HUNTER"))) then
				if	(entites:getType(i)=="ALLY_CITIZEN") and (entites:getDistance(i)==1)
					indice=i
				end

			elseif (not((entites:getType(indice)=="ALLY_CITIZEN") and (entites:getDistance(i)==1))) then
				if (entites:getType(i)=="WILD_ANIMAL") and (entites:isAttackme(i)) then
					indice=i
					nbfoes=nbfoes+1
					sumangle=sumangle+entites:getAngle()
				end

			elseif (entites:getType(i)== "WILD_ANIMAL") then
				nbfoes=nbfoes+1
				sumangle=sumangle+entites:getAngle()

			elseif (entites:getType(i)== "ENEMY_CITIZEN") then
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

			if entites:getType(i)=="HUNTER" then --Chasseur à nous
				indice=i
				nbfoes=nbfoes+1
				sumangle=sumangle+entites:getAngle()

			elseif (not(entites:getType(indice)=="HUNTER")) then
				if entites:getType(i)=="ALLY_CITIZEN" then
					indice=i
					nbfoes=nbfoes+1
					sumangle=sumangle+entites:getAngle()

			--[[elseif (not(entites:getType(indice)=="ALLY_CITIZEN")) then
				if (entites:getType(i)=="PACIFIC_CITIZEN") then
					indice=i
				end]]-- pas d'ennemi neutre pour le moment

			elseif (entites:getType(i)== "WILD_ANIMAL")  then
				nbfoes=nbfoes+1
				sumangle=sumangle+entites:getAngle()

			elseif (entites:getType(i)== "ENEMY_CITIZEN") then
				nbfriends=nbfriends+1
			end
			i=i+1
		end
		if(taille>0) then
			local seuil=nbfriends+2
			if(nbfoes<=seuil) then
				if (not(entites:getType(indice)=="WILD_ANIMAL")) then
					self:setTarget(entites:getId(indice))
					return "attack"
				else
					return "move" --random move
				end
			else
				local moyangle=sumangle/nbfoes
				self:setAngle(moyangle+math.pi)
				return "move"
			end
		else
		return "move" --random move
		end
	end
end
