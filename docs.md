
# conlang docs

*this documentation is in a very crude state and only ment to be usefull to me, others be warned*  

## goals

i am making this language as a personal project in an attempt to change the way i think  
the language should force the user to be explicitly aware of the connections between the words said, pirticularly cause and effect  
i intend this language for personal use, primarily with thinking, secondly with writing and speaking  
the language should be as simple as is reasonable  
the language should sound good  

## phonology

consonants
| |labial|dental|alveolar|post-alveolar|
|---|---|---|---|---|
|nasal          | m | n |   |   |
|sil fricative  |   |   |s/z|x/j|
|fricative      |f/v|t/d|   |   |
|approximant    |   |   |   | r |
|lat approximant|   |   | l |   |

vowels
| |front|central|
|---|---|---|
|close   | i |   |
|mid     | e | w |
|open-mid| a |   |

## morphology

all words are root words  
all words have a trailing vowel
the traling vowel is marking gramatical catagory - see syntax

## semantics

all words are a refrence to an abstract concept  
all further specficity is expresed through context or other words  

## syntax

xatw fwli fwle tatw ladw fwli fwla  
```
          +---+       +---+
riz ->    |xat|-------|tat|
          +---+       +---+
           / \         / \
       +---+ +---+ +---+ +---+
vej +> |fwl| |fwl| |lad| |fwl|
    |  +---+ +---+ +---+ +---+
    |                |
    |              +---+
    +>             |fwl|
                   +---+
```

word order and the trailing vowel give structrue to words  

all word are either a start or a descriptor
- heads are the begining of a clause, they do not provide more information about another word
- speifiers are following a head, of which they provide more information about

all heads are either a cause or a effect
- the cause is the first start, it is the cause of other starts
- effects are following the cause, of which they are effected by

### marking  

all words are marked
there are four kinds of marking

end of a list
- trailing vowel is i
- if the next word is a descriptor of the same word the marked word is, then the next word is said word
- if the next word is a descriptor of another word in the clause, then the next word is a repetition of the descriptee and gets smushed with the trailing vowel
end of a clause
- trailing vowel is e
- next word is a effect
end of a sentance
- trailing vowel is a
- next word is a cause
not an end
- trailing vowel is w
- next word is a descriptor of this word

## borrowing (depricated)

some words are created for their contrast with other words, with english not being considered  
some words are created considering english equivilants, and may be borrowed from an english word  
all borrowed words are CCVV

the prosess by which words get borrowed is as such  

1. assimilation
    - consonant assimilation does not consider sounds, only letters
    - start -> end, unchanged letters not shown
    - c -> y
    - f -> v
    - g -> y
    - k -> y
    - p -> b
    - q -> y
    - s -> z
    - t -> d
    - w -> v
    - x -> z
    - vowel assimiltion does not consider letters, only sounds
    - conlang : english 
    - i : front close
    - e : front mid
    - a : front open, central open, back open
    - u : central close, back close
    - o : central mid, back mid
2. the first vowel is the start of the dipthong V
3. the second vowel is the end of the dipthong, if there is not one, then 'a' is used
3. the consonant before the first vowel is the C before the dipthong
    - if there is no consonant before, then check backwards from the end of the word
4. the consonant before the first consonant is the second C
    - if there is no consonant before, then check backwards from the end of the word
