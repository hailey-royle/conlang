print("dictionary file manipulator")

Def_array = { "baa", "ccc" }

Def_input = "abb"

print(string.sub(Def_input, 1, 1))
print(string.sub(Def_array[1], 1, 1))

Def_array_length = 0
for key, value in pairs(Def_array) do
	Def_array_length = Def_array_length + 1
end
print(Def_array_length)

repeat
	if string.sub(Def_input, 1, 1) > string.sub(Def_array[1], 1, 1) then
		print(">")
	elseif string.sub(Def_input, 1, 1) == string.sub(Def_array[1], 1, 1) then
		print("=")
	--incrementer = incrementer + 1
	else
		print("<")
		table.insert(Def_array, 1, Def_input)
		Def_array_length = Def_array_length + 1
		break
	end
until nil ~= nil

print(Def_array[1])
print(Def_array[2])
print(Def_array[3])
