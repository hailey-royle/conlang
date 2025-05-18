print("english to conlang root word borrower")

--get the user inputed word
io.write("english word: ")
local word = io.read()

--get the user inputed final vowel(its not possible to do this automaticaly)
io.write("conlang vowel: ")
local v_output = io.read()

--dictionary for consonant assimilation
local c_shifts = {
	["c"] = "y",
	["f"] = "v",
	["g"] = "y",
	["k"] = "y",
	["p"] = "b",
	["q"] = "y",
	["s"] = "z",
	["t"] = "d",
	["w"] = "v",
	["x"] = "z",
}

--find unassimilated letters and change them to the corrisponding dictionary value
for key, value in pairs(c_shifts) do
	local incremter = 1
	while string.len(word) >= incremter do
		if string.sub(word, incremter, incremter) == key then
			word = string.gsub(word, key, value)
		end
		incremter = incremter + 1
	end
end

--find the place of the first vowel in the inputed word
local v_place = string.find(word, "[ieaou]")

--(C1)find the letter to the left of the first vowel, or the last consonant
local c1_letter = nil
if v_place == 1 then
	local incremter = string.len(word)
	while c1_letter == nil do
		if string.find(string.sub(word, incremter, incremter), "[ieaou]") then
			incremter = incremter - 1
		else
			c1_letter = string.sub(word, incremter, incremter)
		end
	end
else
	c1_letter = string.sub(word, (v_place - 1), (v_place - 1))
end

--(C2)find the letter to the right of the first vowel
local c2_letter = nil
if v_place == string.len(word) then
	print("bitch you fucked up")
else
	local incremter = v_place + 1
	while c2_letter == nil do
		if string.find(string.sub(word, incremter, incremter), "[ieaou]") then
			incremter = incremter + 1
		else
			c2_letter = string.sub(word, incremter, incremter)
		end
	end
end

--print the final conlang word
print("conlang word: " .. c1_letter .. v_output .. c2_letter)
