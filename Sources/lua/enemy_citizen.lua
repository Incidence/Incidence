--Script citoyen ennemi


function EnemyCitizen:action()
	local entites=self:getEntities()
	local taille=entites:getSize()
	if taille>0 then
		self:setTarget(entites:getID(0))
		return "attack"
	end
	return "move"
	--local entites=self:getEntities()
	--local taille=entites:getSize()
	
	--if self:isAttacked() then
		--local i=1
		--local indice=1
		--while (i<=taille) and (not((entites:getStatut(i)=="ALLY_CITIZEN") && (entites:getDistance(i)==1))) do -- priorité aux citoyens risque de tout parcourir(sinon on fait un || entre animaux agressifs  et citoyens.
			--if 	entites:getStatut(i)=="WILD_ANIMAL"  and (entites:getDistance(i)==1) then
				--indice=i
			--end
			--i=i+1
		--end
		--if i<=taille then
			--self:setAngle(entites:getAngle(i))
			--return "attack"
		--else
			--self:setAngle(entites:getAngle(indice))
			--return "attack"
		--end
	--else
		--local i=1
		--local indice=0		
		--while(i<=taille) and (not(entites:getStatut(i)=="ALLY_CITIZEN"))do --attaque les citoyens en priorité
			--if entites:getStatut(i)=="PEACEFUL_ANIMAL" then -- cherche à "saborder" les ressources
				--indice=i							   -- du - au + risqué	
			--elseif entites:getStatut(i)=="WILD_ANIMAL" and indice==0 then
				--incide=i
			--end
			--i=i+1
		--end
		--if i<=taille  and taille>=1 then
			--self:setAngle(entites:getAngle(i))
			--if entites:getDistance(i)==1 then
				--return "attack"
			--end
		--elseif indice~=0
			--self:setAngle(entites:getAngle(indice))
			--if entites:getDistance(indice)==1 then
				--return "attack"
			--end
		--end													
		--return "move"										
	--end
end
																	