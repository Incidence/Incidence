function Entity:action()
	print("Salut 2 !");
	local b = self:restart();
	if b then
		print("Salut Boolette !");
	end
	
	if self:getType() == CITIZEN then
		print("Citizen");
	end
end