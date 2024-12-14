import copy
import pprint

valid = 0

def is_valid(res, num_list):
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
        #print(f"res divisible par last : {res} / {last}")
        if is_valid(res//last, num_list.copy()):
            return True
    else: 
        #print(f"res not divisible par last : {res} / {last}, substracting {last} from {res} = {res-last}")
        return is_valid(res-last, num_list.copy())
            

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
            print(f"TRUE  ->  {line.strip()}")
        else:
            print(f"FALSE ->  {line.strip()}")
  
print(valid)      

