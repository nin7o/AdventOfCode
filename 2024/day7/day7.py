import copy
import pprint

valid = 0
valid2 = 0

#q,r = divmod(10, 3)

def is_valid(res, num_list):
    last = num_list.pop()
    if len(num_list) == 0:
        return last == res
    if res % last == 0:
        if is_valid(res//last, num_list.copy()):
            return True
    if res - last >= 0: 
        return is_valid(res-last, num_list.copy())
    else:
        return False
  
def is_valid_p2(res, num_list):
    last = num_list.pop()
    print(f"res = {res}, last = {last}, num_list = {num_list}")
    if len(num_list) == 0:
        return last == res
    if res % last == 0:
        print(f"on tente la division : {res} / {last}")
        if is_valid_p2(res//last, num_list.copy()):
            return True
    if res - last >= 0: 
        print(f"on tente la soustraction : substracting {last} from {res} = {res-last}")
        if is_valid_p2(res-last, num_list.copy()):
            return True
    res_str = str(res)
    last_str = str(last)
    if res_str.endswith(last_str):
        new_res = int(res_str[:-len(last_str)])
        if is_valid_p2(new_res, num_list.copy()):
            return True
    
            

with open ('input', 'r') as f:
    data = f.readlines()
    for line in data:
        line2 = line.strip().split(':')
        res = int(line2[0])
        operands = [int(x) for x in line2[1].split()]
        if is_valid(copy.deepcopy(res), copy.deepcopy(operands)):
            valid += res
            valid2 += res
        elif is_valid_p2(copy.deepcopy(res), copy.deepcopy(operands)):
            valid2 += res
            print(f"TRUE -> {res}")
        else:
            print(f"FALSE -> {res}")
  
print("Part 1 : ", valid)
print("Part 2 : ", valid2) 
