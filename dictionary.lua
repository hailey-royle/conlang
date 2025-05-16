print("conlang dictionary file manipulator")

local def_search = nil
local def_add = nil

--get the user's instructions
io.write("search(s), add definition(a), quit(q): ")
local instructions = io.read()
if instructions == "s" then
	io.write('search for word("~word " for conlang "-word " for english): ')
	def_search = io.read()
elseif instructions == "a" then
	io.write('definition to put in dictionary("~conlang : definition : -english): ')
	def_add = io.read()
elseif instructions == "q" then
	print("quit")
else
	print("else")
end

--get dictionary from dictionary.txt and put it into def_table
local def_table = {}
for line in io.lines("dictionary.txt") do
	table.insert(def_table, line)
end

if instructions == "s" then
	--prints all lines with def_search
	local inc_found = 0
	for i = 1, #def_table do
		if string.find(def_table[i], def_search) then
			print(def_table[i])
			inc_found = inc_found + 1
		end
	end
	if inc_found == 0 then
		print("nothing found")
	end
end

if instructions == "a" then
	--add the new definition to the place before the first "bigger" definition(alphabetical order)
	--inc_down is incrementing what definiton is checked
	local inc_down = 1
	--inc_in is incremeting what letter is checked
	local inc_in = 2
	repeat
		if string.sub(def_add, inc_in, inc_in) > string.sub(def_table[inc_down], inc_in, inc_in) then
			inc_down = inc_down + 1
			inc_in = 2
		elseif string.sub(def_add, inc_in, inc_in) == string.sub(def_table[inc_down], inc_in, inc_in) then
			inc_in = inc_in + 1
		else
			table.insert(def_table, inc_down, def_add)
			break
		end
	until nil ~= nil
	--add def_table to temp file, clones temp file to file, deletes temp file
	io.output("temp_dictionary.txt")
	for i = 1, #def_table do
		io.write(def_table[i], "\n")
	end
	os.rename("temp_dictionary.txt", "dictionary.txt")
	os.remove("temp_dictionary.txt")
end
