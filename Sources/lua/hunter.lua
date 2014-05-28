--Script chasseur


function Hunter:action()

	local MAXDISTANCE=10 --Distance max de la base si le hunter ne voit rien
	local MAXDISTANCEHUNT=40 --Distance max de la base si le hunter voit une "proie"

	local entites=self:getEntities()
	local taille=entites:getSize()
	local i=1
	local indice=1
	local nbfoes=0
	local nbfriends=0


	--print(self:getDistanceToHome())
	if self:isAttacked() then
	--print("estattaque")

		local sumangle=0
		while (i<=taille) do

			if (self:isAttackMe(entites:getID(i))) and (entites:getAngle(i)==self:getAngle()) then
				indice=i

			elseif (not((self:isAttackMe(entites:getID(indice))) and (entites:getAngle(indice)==self:getAngle()))) then
				if (self:isAttackMe(entites:getID(i))) and (entites:getType(i)==ENEMY_CITIZEN) then
					indice=i

				elseif (not(self:isAttackMe(entites:getID(indice)) and entites:getType(indice)==ENEMY_CITIZEN)) then
					if (entites:getType(i)==ENEMY_CITIZEN) and (self:getDistance(entites:getID(i))==1) then
						indice=i

					elseif (not((entites:getType(indice)==ENEMY_CITIZEN) and (self:getDistance(entites:getID(indice))==1))) then
						if (entites:getType(i)==WILD_ANIMAL) and (self:isAttackMe(entites:getID(i))) then
							indice=i
						end
					end
				end

			elseif (entites:getType(i)== WILD_ANIMAL)  or (entites:getType(i)==ENEMY_CITIZEN) then
				nbfoes=nbfoes+1
				sumangle=sumangle+entites:getAngle(i)

			elseif (entites:getType(i)== HUNTER) then
				nbfriends=nbfriends+1
			end
			i=i+1
		end

		local seuil=nbfriends+1
		if(nbfoes<=seuil) then
			self:setTarget(entites:getID(indice))
			return "attack"
		else
			local moyangle=sumangle/nbfoes     -- j'ai gardé le fait qu'il prenne le "meilleur angle" pour fuir mais sinon
			self:setAngle(moyangle+math.pi)		-- on peut mettre self:setAngle(self:getAngleToHome()) pour qu'il revienne a la maison
			return "move"						-- pour ne pas risquer qu'il s'eloigne à jamais de la base(mini risque)
		end

	else

		local sumangle=0
		while (i<=taille) do

			if (entites:getType(i)==ENEMY_CITIZEN) and (self:getDistanceToHome(entites:getID(i))<=MAXDISTANCEHUNT) then
				indice=i

			elseif (not(entites:getType(indice)==ENEMY_CITIZEN)) then
				if (entites:getType(i)==WILD_ANIMAL) and (self:getDistanceToHome(entites:getID(i))<=MAXDISTANCEHUNT) then
					indice=i
				elseif (not(entites:getType(indice)==WILD_ANIMAL)) then
					if (entites:getType(i)==PEACEFUL_ANIMAL) and (self:getDistanceToHome(entites:getID(i))<=MAXDISTANCEHUNT) then
						indice=i
					end
				end
			end

			if (entites:getType(i)== WILD_ANIMAL) or (entites:getType(i)==ENEMY_CITIZEN) then
				nbfoes=nbfoes+1
				sumangle=sumangle+entites:getAngle(i)
			end

			if (entites:getType(i)==HUNTER) then
				nbfriends=nbfriends+2
			end
			i=i+1
		end
		if(taille>0) then
			local seuil=nbfriends+1
			if(nbfoes<=seuil) then
				if (not ((entites:getType(indice)==ALLY_CITIZEN) or (entites:getType(indice)==HUNTER))) and (self:getDistanceToHome(entites:getID(indice))<=MAXDISTANCEHUNT) then
					self:setTarget(entites:getID(indice))
					--print("ennemi")
					return "attack"
				else
					--print("no ennemi")

					if(self:getDistanceToHome()>MAXDISTANCE) or  (self:getDistanceToHome()==MAXDISTANCE) then
					--print("sup")
					self:setAngle(self:getAngle()+math.pi)
					return "move"
					end


					if(self:getDistanceToHome()<MAXDISTANCE) then
						--print("sous")
						local rand = self:getRandom()%3
						if rand == 1 then
							self:setAngle((self:getAngle()-(math.pi/4))%2*math.pi)
						elseif rand == 2 then
							self:setAngle((self:getAngle()+(math.pi/4))%2*math.pi)
						end
						return "move"
					end
				end
			else
				local moyangle=sumangle/nbfoes
				self:setAngle((moyangle+math.pi)%2*math.pi)
				return "move"
			end
		else
		--print("no perception")

			math.randomseed(os.time())
			math.random()
			math.random()

			if(self:getDistanceToHome()>MAXDISTANCE) or (self:getDistanceToHome()==MAXDISTANCE) then
				--print("sup")
				self:setAngle(self:getAngle()+math.pi)
				return "move"
			end


			if(self:getDistanceToHome()<MAXDISTANCE) then
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
end


