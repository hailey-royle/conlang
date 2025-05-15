print("dictionary file manipulator")

--the dictionary
--TODO make the dictionary read from a file
--the last value needs to be a z because the deffinition adder has a stroke if it needs to add at the end of the array, so the z means it always has something after
--TODO get rid of the fucking z its so ugly
Def_table = { "aaa", "bbb", "z" }

--definition to be added to the dictionary
--TODO make this be a actual user input
Def_input = "ccc"

--add the new definition to the place before the first "bigger" definition(alphabetical order)
--inc_down is incrementing what definiton is checked
local inc_down = 1
--inc_in is incremeting what letter is checked
local inc_in = 1
repeat
	if string.sub(Def_input, inc_in, inc_in) > string.sub(Def_table[inc_down], inc_in, inc_in) then
		inc_down = inc_down + 1
		inc_in = 1
	elseif string.sub(Def_input, inc_in, inc_in) == string.sub(Def_table[inc_down], inc_in, inc_in) then
		inc_in = inc_in + 1
	else
		table.insert(Def_table, inc_down, Def_input)
		break
	end
until nil ~= nil

--temporary output
print(Def_table[1])
print(Def_table[2])
print(Def_table[3])
