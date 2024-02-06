import math
import pprint
import portion

inputFile = "input"
isRules = True
ruleDict = {}
inputDict = {}
totalSum = 0

def checkRule(rule, values):
    ruleList = ruleDict[rule]
    ruleLen = len(ruleList)
    for i in range(ruleLen - 1):
        if "<" in ruleList[i]:
            valuestocompare = ruleList[i].split(":")[0].split("<")
            if int(inputDict[valuestocompare[0]]) < int(valuestocompare[1]):
                return ruleList[i].split(":")[1]
        elif ">" in ruleList[i]:
            valuestocompare = ruleList[i].split(":")[0].split(">")
            if int(inputDict[valuestocompare[0]]) > int(valuestocompare[1]):
                return ruleList[i].split(":")[1]
    return ruleList[ruleLen - 1]

with open(inputFile, "r") as file:
    for line in file:
        if line == "\n":
            isRules = False
            continue
        line = line.strip()
        if isRules:
            ruleName = line.split("{")[0]
            ruleList = line.split("{")[1].split("}")[0].split(",")
            ruleDict[ruleName] = ruleList
            
        if not isRules:
            inputDict = {}
            pairs = line.strip('{}').split(",")
            for pair in pairs:
                key, value = pair.split("=")
                inputDict[key] = value
            
            answer = "in"
            while answer != "R" and answer != "A":
                answer = checkRule(answer, inputDict)
                
            if answer == "A":
                totalSum += int(inputDict["x"])
                totalSum += int(inputDict["m"])
                totalSum += int(inputDict["a"])
                totalSum += int(inputDict["s"])
            
print("Part 1:", totalSum)

for key, valueList in ruleDict.items():
    keyList = []
    for value in valueList:
        ruleAsList = []
        if "<" in value:
            ruleAsList.append(value.split("<")[0])
            ruleAsList.append("<")
            ruleAsList.append(value.split("<")[1].split(":")[0])
            ruleAsList.append(value.split("<")[1].split(":")[1])
        elif ">" in value:
            ruleAsList.append(value.split(">")[0])
            ruleAsList.append(">")
            ruleAsList.append(value.split(">")[1].split(":")[0])
            ruleAsList.append(value.split(">")[1].split(":")[1])
        else:
            ruleAsList.append(value)
        keyList.append(ruleAsList)
    ruleDict[key] = keyList
  

def sizeOfInterval(interval):
    if interval.empty:
        return 1
    else:
        return interval.upper - interval.lower + 1

def combinaisons(intervals):
    return sizeOfInterval(intervals["x"]) * sizeOfInterval(intervals["m"]) * sizeOfInterval(intervals["a"]) * sizeOfInterval(intervals["s"])
        
Xinterval = portion.closed(1,4000)
Minterval = portion.closed(1,4000)
Ainterval = portion.closed(1,4000)
Sinterval = portion.closed(1,4000)

startIntervals = {"x" : Xinterval, "m" : Minterval, "a" : Ainterval, "s" : Sinterval}

#return how many combinaisons follow the rules
def countCombinations(rule, intervals):
    print(rule, intervals)
    if rule == "R":
        return 0
    elif rule == "A":
        return combinaisons(intervals)
    else:
        ValidCombinaisons = 0
        ruleList = ruleDict[rule]
        ruleLen = len(ruleList)
        for rule in ruleList:
            if rule == "R":
                ValidCombinaisons += 0
            if rule == "A":
                ValidCombinaisons += combinaisons(intervals)
            elif len(rule) == 1:
                ValidCombinaisons += countCombinations(rule[0], intervals)
            else:
                letter = rule[0]
                operator = rule[1]
                value = int(rule[2])
                newRule = rule[3]
                if operator == "<":
                    newIntervals = intervals.copy()
                    lowerInterval = portion.closed(1, value - 1)
                    upperInterval = portion.closed(value, 4000)
                    newIntervals[letter] = lowerInterval & intervals[letter]
                    intervals[letter] = upperInterval & intervals[letter]
                    ValidCombinaisons += countCombinations(newRule, newIntervals)
                elif operator == ">":
                    newIntervals = intervals.copy()
                    lowerInterval = portion.closed(1, value)
                    upperInterval = portion.closed(value + 1, 4000)
                    newIntervals[letter] = upperInterval & intervals[letter]
                    intervals[letter] = lowerInterval & intervals[letter]
                    ValidCombinaisons += countCombinations(newRule, newIntervals)
        return ValidCombinaisons
    
print("Part 2:", countCombinations("in", startIntervals))
print("test 2: 167409079868000")