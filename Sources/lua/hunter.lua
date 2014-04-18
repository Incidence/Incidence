--Script chasseur


function Hunter:action()

	local MAXDISTANCE=5 --Distance max de la base si le hunter ne voit rien
	local MAXDISTANCEHUNT=10 --Distance max de la base si le hunter voit une "proie"

	local entites=self:getEntities()
	local taille=entites:getSize()
	local i=1
	local indice=1
	local nbfoes=0
	local nbfriends=0

	if self:isAttacked() then

		local sumangle=0
		while (i<=taille) do

			if (entites:isAttackMe(entities:getID(i))) and (entites:getAngle(i)==self:getAngle()) then
				indice=i

			elseif (not((entites:isAttackMe(entities:getID(indice))) and (entites:getAngle(indice)==self:getAngle()))) then
				if (entites:isAttackMe(entities:getID(i))) and (entites:getType(i)=="ENEMY_CITIZEN") then
					indice=i

				elseif (not(entites:isAttackMe(entities:getID(indice)) and entites:getType(indice)=="ENEMY_CITIZEN")) then
					if (entites:getType(i)=="ENEMY_CITIZEN") and (entites:getDistance(i)==1) then
						indice=i

					elseif (not((entites:getType(indice)=="ENEMY_CITIZEN") and (entites:getDistance(indice)==1))) then
						if (entites:getType(i)=="WILD_ANIMAL") and (entites:isAttackMe(entities:getID(i))) then
							indice=i
						end
					end
				end

			elseif (entites:getType(i)== "WILD_ANIMAL")  or (entites:getType(i)=="ENEMY_CITIZEN") then
				nbfoes=nbfoes+1
				sumangle=sumangle+entites:getAngle()

			elseif (entites:getType(i)== "HUNTER") then
				nbfriends=nbfriends+1
			end
			i=i+1
		end

		local seuil=nbfriends+2
		if(nbfoes<=seuil) then
			self:setTarget(entites:getId(indice))
			return "attack"
		else
			local moyangle=sumangle/nbfoes     -- j'ai gardé le fait qu'il prenne le "meilleur angle" pour fuir mais sinon
			self:setAngle(moyangle+math.pi)		-- on peut mettre self:setAngle(self:getAngleToHome()) pour qu'il revienne a la maison
			return "move"						-- pour ne pas risquer qu'il s'eloigne à jamais de la base(mini risque)
		end

	else

		local sumangle=0
		while (i<=taille) do

			if (entites:getType(i)=="ENEMY_CITIZEN") and (entites:getDistanceToHome(i)<=MAXDISTANCEHUNT) then
				indice=i

			elseif (not(entites:getType(indice)=="ENEMY_CITIZEN")) then
				if (entites:getType(i)=="WILD_ANIMAL") and (entites:getDistanceToHome(i)<=MAXDISTANCEHUNT) then
					indice=i
				elseif (not(entites:getType(indice)=="WILD_ANIMAL")) then
					if (entites:getType(i)=="PEACEFUL_ANIMAL") and (entites:getDistanceToHome(i)<=MAXDISTANCEHUNT) then
						indice=i
					end
				end
			end

			if (entites:getType(i)== "WILD_ANIMAL") or (entites:getType(i)=="ENEMY_CITIZEN") then
				nbfoes=nbfoes+1
				sumangle=sumangle+entites:getAngle()
			end

			if (entites:getType(i)=="HUNTER") then
				nbfriends=nbfriends+1
			end
			i=i+1
		end
		if(taille>0) then
			local seuil=nbfriends+2
			if(nbfoes<=seuil) then
				if (not ((entites:getType(indice)=="ALLY_CITIZEN") or (entites:getType(indice)=="HUNTER"))) and (entites:getDistanceToHome(i)<=MAXDISTANCEHUNT) then
					self:setTarget(entites:getId(indice))
					return "attack"
				else
					if(self:getDistanceToHome()>MAXDISTANCE)
					self:setAngle(self:getAngleToHome())
					return "move"

					else
						math.randomseed(os.time())
						math.random()
						math.random()

						if(self:getDistanceToHome()==MAXDISTANCE)
							local angleoppose=((self:getDistanceToHome()+math.pi))%2*math.pi
							local angleinterditmin=((self:getDistanceToHome()+math.pi)+math.pi/2)%2*math.pi
							local angleinterditmax=((self:getDistanceToHome()+math.pi)-math.pi/2)%2*math.pi
							repeat
								local rand = math.floor(math.random()*10000)%5
								--print(rand)
								if rand == 0 then
									local angle=self:getAngle()-math.pi/2
								elseif rand == 4 then
									local angle=self:getAngle()+math.pi/2
								else
									local angle=self:getAngle()
								end
							until (angle>angleinterditmin) and (angle<angleinterditmax)
							self:setAngle(angle)
							return "move"

						elseif(self:getDistanceToHome()<MAXDISTANCE)
							local rand = math.floor(math.random()*10000)%5
							--print(rand)
							if rand == 0 then
								local angle=self:getAngle()-math.pi/2
							elseif rand == 4 then
								local angle=self:getAngle()+math.pi/2
							else
								local angle=self:getAngle()
							end
							self:setAngle(angle)
							return "move"
						end
					end
				end
			else
				local moyangle=sumangle/nbfoes
				self:setAngle(moyangle+math.pi)
				return "move"
			end
		else

			if(self:getDistanceToHome()>MAXDISTANCE)
				self:setAngle(self:getAngleToHome())
				return "move"

			else
				math.randomseed(os.time())
				math.random()
				math.random()

				if(self:getDistanceToHome()==MAXDISTANCE)
					local angleoppose=((self:getDistanceToHome()+math.pi))%2*math.pi
					local angleinterditmin=((self:getDistanceToHome()+math.pi)+math.pi/2)%2*math.pi
					local angleinterditmax=((self:getDistanceToHome()+math.pi)-math.pi/2)%2*math.pi
					repeat
						local rand = math.floor(math.random()*10000)%5
						--print(rand)
						if rand == 0 then
							local angle=self:getAngle()-math.pi/2
						elseif rand == 4 then
							local angle=self:getAngle()+math.pi/2
						else
							local angle=self:getAngle()
						end
					until (angle>angleinterditmin) and (angle<angleinterditmax)
					self:setAngle(angle)
					return "move"

				elseif(self:getDistanceToHome()<MAXDISTANCE)
					local rand = math.floor(math.random()*10000)%5
					--print(rand)
					if rand == 0 then
						local angle=self:getAngle()-math.pi/2
					elseif rand == 4 then
						local angle=self:getAngle()+math.pi/2
					else
						local angle=self:getAngle()
					end
					self:setAngle(angle)
					return "move"
				end
			end
		end
	end
end


