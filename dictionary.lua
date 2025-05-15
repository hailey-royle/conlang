print("dictionary file manipulator")

--get dictionary from dictionary.txt and put it into def_table
local def_table = {}
local def_raw = io.open("dictionary.txt", "r")
if def_raw ~= nil then
	local incremter = 1
	local write_def = def_raw:read("*l")
	while write_def ~= nil do
		def_table[incremter] = write_def
		incremter = incremter + 1
		write_def = def_raw:read("*l")
	end
	def_raw:close()
else
	print("file not found")
end

--definition to be added to the dictionary
--TODO make this be a actual user input
local def_input = "ccc"

--add the new definition to the place before the first "bigger" definition(alphabetical order)
--inc_down is incrementing what definiton is checked
local inc_down = 1
--inc_in is incremeting what letter is checked
local inc_in = 1
repeat
	if string.sub(def_input, inc_in, inc_in) > string.sub(def_table[inc_down], inc_in, inc_in) then
		inc_down = inc_down + 1
		inc_in = 1
	elseif string.sub(def_input, inc_in, inc_in) == string.sub(def_table[inc_down], inc_in, inc_in) then
		inc_in = inc_in + 1
	else
		table.insert(def_table, inc_down, def_input)
		break
	end
until nil ~= nil

--temporary output
print(def_table[1])
print(def_table[2])
print(def_table[3])
print(def_table[4])
