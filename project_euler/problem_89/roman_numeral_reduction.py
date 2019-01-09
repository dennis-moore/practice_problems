import sys

DEFAULT_FILE = "roman.txt"
# string replacement rules drawn from problem; the 5 character rules must be searched and replaced first
replacementRules = [
    ("VIIII", "IX"),
    ("IIII", "IV"),
    ("LXXXX", "XC"),
    ("XXXX", "XL"),
    ("DCCCC", "CM"),
    ("CCCC", "CD"),
]

class RomanNumeralReduction:

    def __init__(self, filePath):
        self.filePath = filePath

    #loop through rule list and replace any matching strings with their shorter equivalent
    def minimizeNumeral(self, romanNumeral):
        reducedNumeral = romanNumeral
        for long, short in replacementRules:
            reducedNumeral = reducedNumeral.replace(long, short)
        return reducedNumeral

    #loop through lines of file and apply the reduction, summing up the character savings for each line
    def doReduction(self):
        with open(self.filePath, 'r') as file:
            savings = 0
            for romanNumeral in file:
                romanNumeral.strip() #remove whitespaces
                savings += len(romanNumeral) - len(self.minimizeNumeral(romanNumeral)) #sum up character savings for each line
            return savings

if __name__ == '__main__':
    if len(sys.argv) == 1:
        filePath = DEFAULT_FILE
    else:
        filePath = sys.argv[1]
    romanNumeral = RomanNumeralReduction(filePath)
    print(romanNumeral.doReduction())
