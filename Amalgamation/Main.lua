

Str = "Hey, it works\n";

main = function() --Entry point

	io.write(Str);

	Str = io.read();

	io.write(Str);

	io.read();

end