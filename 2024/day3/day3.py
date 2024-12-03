import pprint
import itertools
import re

pattern = r"mul\((\d{1,3}),(\d{1,3})\)"
pattern_do = r"do\(\)"
pattern_dont = r"don\'t\(\)"
combined_pattern = f"{pattern}|{pattern_do}|{pattern_dont}"
data = ""
total = 0
total_1 = 0
do = True

with open ('input', 'r') as f:
    lines = f.readlines()
    for line in lines:
        data = line.strip()
        print(data)
        for match in re.finditer(combined_pattern, data):
            print(match.group())
            if re.search(pattern, match.group()):
                total_1 += int(match.group(1)) * int(match.group(2))
                total += int(match.group(1)) * int(match.group(2)) if do else 0
            elif re.search(pattern_do, match.group()):
                do = True
            elif re.search(pattern_dont, match.group()):
                do = False
        
print("p1 :", total_1)
print("p2 :", total)