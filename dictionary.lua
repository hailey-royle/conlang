print("dictionary file manipulator")

--get dictionary from dictionary.txt and put it into def_table
local def_table = {}
for line in io.lines("dictionary.txt") do
	table.insert(def_table, line)
end

--user definition to be added to the dictionary
io.write("definition to put in dictionary: ")
local def_input = io.read()

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

--add def_table to temp file, clones temp file to file, deletes temp file
io.output("temp_dictionary.txt")
for i = 1, #def_table do
	io.write(def_table[i], "\n")
end
os.rename("temp_dictionary.txt", "dictionary.txt")
os.remove("temp_dictionary.txt")

--prints all lines with def_search
local def_search = "and"
for i = 1, #def_table do
	if string.find(def_table[i], def_search) then
		print(def_table[i])
	end
end
