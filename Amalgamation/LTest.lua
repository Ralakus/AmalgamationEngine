function Awake()
	
	--[[local T = AE.Time:new()

	while (not T:OnSecond()) do

		T:Update()
		
	end]]

	TStr = AE.ReadFile("Path.lua")

	io.write(TStr .. "\n")

	if(TStr == "") then
		io.write("[READ ERROR]: Failed to read file \"Path.lua\"")
	end

	io.write("Amalgamation Load Done\n")

end

function Update(Delta)
	--[[if(AE.IsKeyDown(ToByte('W'))) then
		io.write("W down\n")
	end
	if(AE.IsKeyDown(ToByte('A'))) then
		io.write("A down\n")
	end
	if(AE.IsKeyDown(ToByte('S'))) then
		io.write("S down\n")
	end
	if(AE.IsKeyDown(ToByte('D'))) then
		io.write("D down\n")
	end

	if(AE.IsKeyDown(ToByte('Q'))) then
		io.write("Q down\n")
	end
	if(AE.IsKeyDown(ToByte('E'))) then
		io.write("E down\n")
	end]]
end

function Destroy()

end

function ToByte(Char)
	return string.byte(Char)
end