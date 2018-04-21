function Awake()

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