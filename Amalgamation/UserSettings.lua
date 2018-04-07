UserSettings = {
	Window = {
		Title = "Noice",
		Width = 1920,
		Height = 1080,
		Fullscreen = false,
	},

	MouseSensitivity = 3.5,
	MovementSpeed = 3.5,

	CameraFOV = 90,

	TextureVariable0 = "container2.png",
	TextureVariable1 = "container2.png",
}

function CheckUserSettings()

	if(UserSettings["Window"]["Width"] <= 0) then
		UserSettings["Window"]["Width"] = 800
		io.write("Window Width set to 800 due to being invalid\n")
	end
	if(UserSettings["Window"]["Height"] <= 0) then
		UserSettings["Window"]["Height"] = 600
		io.write("Window Height set to 600 due to being invalid\n")
	end
	if(UserSettings["Window"]["Fullscreen"] == nil or type(UserSettings["Window"]["Fullscreen"]) ~= "boolean") then
		UserSettings["Window"]["Fullscreen"] = false
		io.write("Window Fullscreen set to false due to being invalid\n")
	end
	--[[ Need to fix error checking for these
	if(UserSettings["Window"]["MouseSensitivity"] == nil or type(UserSettings["Window"]["MouseSensitivity"]) ~= "number") then
		UserSettings["Window"]["MouseSensitivity"] = 1
		io.write("Mouse Sensitivity set to 1 due to being invalid\n")
	end
	if(UserSettings["Window"]["MovementSpeed"] == nil or type(UserSettings["Window"]["MovementSpeed"]) ~= "number") then
		UserSettings["Window"]["MovementSpeed"] = 1
		io.write("Movement Speed set to 1 due to being invalid\n")
	end

	if(UserSettings["Window"]["MovementSpeed"] == nil or type(UserSettings["Window"]["CameraFOV"]) ~= "number") then
		UserSettings["Window"]["CameraFOV"] = 90
		io.write("Camera FOV set to 90 due to being invalid\n")
	end
	]]

end