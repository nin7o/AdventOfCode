import copy
import pprint

valid = 0
valid2 = 0

def is_valid(res, num_list):
    last = num_list.pop()
    #print(f"res = {res}, last = {last}, num_list = {num_list}")
    if len(num_list) == 0:
        if last == res:
            print(f"res == last : {res} == {last} -> True")
            return True
        else:
            #print(f"res != last : {res} != {last} -> False")
            return False
    if res % last == 0:
        #print(f"on tente la division : {res} / {last}")
        if is_valid(res//last, num_list.copy()):
            return True
        else:
            #print(f"la div a pas marchée : {res} / {last}, substracting {last} from {res} = {res-last}")
            return is_valid(res-last, num_list.copy())
    else: 
        #print(f"on tente la soustraction : substracting {last} from {res} = {res-last}")
        return is_valid(res-last, num_list.copy())
    
def is_valid_p2(res, num_list):
    last = num_list.pop()
    #print(f"res = {res}, last = {last}, num_list = {num_list}")
    if len(num_list) == 0:
        if last == res:
            #print(f"res == last : {res} == {last} -> True")
            return True
        else:
            #print(f"res != last : {res} != {last} -> False")
            return False
    if res % last == 0:
        #print(f"on tente la division : {res} / {last}")
        if is_valid_p2(res//last, num_list.copy()):
            return True
        else:
            #print(f"la div a pas marchée : {res} / {last}, substracting {last} from {res} = {res-last}")
            if is_valid_p2(res-last, num_list.copy()):
                return True
            else:
                #print(f"la soustraction a pas marchée : {res} - {last} -> on tente la concaténation : {res}{last}")
                new_list = num_list.copy()
                new_list[-1] = int(str(new_list[-1]) + str(last))
                #print(f"new_list = {new_list}")
                return is_valid_p2(res, new_list)
    else: 
        #print(f"on tente la soustraction : substracting {last} from {res} = {res-last}")
        if is_valid_p2(res-last, num_list.copy()):
            return True
        else:
            #print(f"la soustraction a pas marchée : {res} - {last} -> on tente la concaténation : {res}{last}")
            new_list = num_list.copy()
            new_list[-1] = int(str(new_list[-1]) + str(last))
            return is_valid_p2(res, new_list)
            

with open ('input', 'r') as f:
    data = f.readlines()
    for line in data:
        line2 = line.strip().split(':')
        res = int(line2[0])
        operands = [int(x) for x in line2[1].split()]
        #print("====================================")
        #print(operands)
        if is_valid(copy.deepcopy(res), operands):
            valid += res
            valid2 += res
        elif is_valid_p2(copy.deepcopy(res), operands):
            valid2 += res
  
print("Part 1 : ", valid)
print("Part 2 : ", valid2) 
