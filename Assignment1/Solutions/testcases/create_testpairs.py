
import random
from typing import List, Tuple

import os
os.chdir(os.path.dirname(__file__))


def generate_pairs(method_names: List[int], size: int, r_start: int, r_end: int) -> List[Tuple[str, int]]:
    pairs = list()
    for _ in range(size):
        input = random.randint(r_start, r_end)
        m_index = random.randint(0, len(method_names)-1)
        pair = (method_names[m_index], input)
        pairs.append(pair)
    
    return pairs

def write_pairs(file_name: str, pairs: List[Tuple[str, int]]) -> None:
    with open(file_name, "w") as file:
        for pair in pairs:
            file.write("{} {}\n".format(pair[0], pair[1]))
        


if __name__ == '__main__':
    method_names = ['add', 'rmv', 'ctn']
    file_size = 5
    task_name = 'T3'

    for i in range(file_size):
        fn = "{}{}.txt".format(task_name+'TEST_', i)
        write_pairs(fn, generate_pairs(method_names, size=100, r_start=1, r_end=100))