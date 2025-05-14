print("english to conlang root word borrower")

--get the user inputed word
io.write("english word: ")
Word = io.read()

--get the user inputed final vowel(its not possible to do this automaticaly)
io.write("conlang vowel: ")
V_output = io.read()

--dictionary for consonant assimilation
C_shifts =
	{ ["c"] = "k", ["f"] = "w", ["h"] = "y", ["j"] = "r", ["q"] = "k", ["v"] = "w", ["s"] = "", ["x"] = "", ["z"] = "" }

--find unassimilated letters and change them to the corrisponding dictionary value
for key, value in pairs(C_shifts) do
	local incremter = 1
	while string.len(Word) >= incremter do
		if string.sub(Word, incremter, incremter) == key then
			Word = string.gsub(Word, key, value)
		end
		incremter = incremter + 1
	end
end

--find the place of the first vowel in the inputed word
V_place = string.find(Word, "[ieaou]")

--(C1)find the letter to the left of the first vowel, or the last consonant
if V_place == 1 then
	local incremter = string.len(Word)
	while C1_letter == nil do
		if string.find(string.sub(Word, incremter, incremter), "[ieaou]") then
			incremter = incremter - 1
		else
			C1_letter = string.sub(Word, incremter, incremter)
		end
	end
else
	C1_letter = string.sub(Word, (V_place - 1), (V_place - 1))
end

--(C2)find the letter to the right of the first vowel
if V_place == string.len(Word) then
	print("bitch you fucked up")
else
	local incremter = V_place + 1
	while C2_letter == nil do
		if string.find(string.sub(Word, incremter, incremter), "[ieaou]") then
			incremter = incremter + 1
		else
			C2_letter = string.sub(Word, incremter, incremter)
		end
	end
end

--print the final conlang word
print("conlang word: " .. C1_letter .. V_output .. C2_letter)
