import copy
import pprint
import time

line = []

with open ('input', 'r') as f:
    data = f.read().strip()
    pprint.pprint(data)
    line = list(data)
    line = [int(x) for x in line]
    
    
def compute_checksum(line):
    cksm = 0
    global_index = 0
    value_index = 0
    val_to_add = 0
    val_to_add_last = len(line) // 2
    last_index = len(line) - 1
    sizes = copy.deepcopy(line)
    while value_index < len(sizes):
        is_bloc = value_index % 2 == 0
        is_last_bloc = last_index % 2 == 0
        #print last 25 elements of sizes
        print(sizes[-25:])
        if sizes[value_index] != 0:
            if is_bloc:
                cksm += val_to_add * global_index
                print(f"adding {val_to_add} * {global_index} to cksm")
                #time.sleep(0.5)
                sizes[value_index] = sizes[value_index] - 1
                global_index += 1
            else:
                if not is_last_bloc:
                    sizes.pop(last_index)
                    last_index -= 1
                    val_to_add_last -= 1
                else:
                    if sizes[last_index] != 0:
                        cksm += val_to_add_last * global_index
                        print(f"adding {val_to_add_last} * {global_index} to cksm")
                        #time.sleep(0.5)
                        sizes[last_index] = sizes[last_index] - 1
                        global_index += 1
                        sizes[value_index] = sizes[value_index] - 1
                        if sizes[value_index] == 0:
                            value_index += 1
                            val_to_add += 1
                    else:
                        sizes.pop(last_index)
                        last_index -= 1
        else:
            value_index += 1
    return cksm

print("p1       :",compute_checksum(line))
print("expected : 6421128769094")
            
        
        
    
    