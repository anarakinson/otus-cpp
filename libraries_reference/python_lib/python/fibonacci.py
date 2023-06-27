import sys
import os
from typing import List


# Adding path to the module search path list 
module_dir = os.path.dirname(os.path.abspath(__file__))
project_root_dir = os.path.dirname(module_dir)
module_path = os.path.join(project_root_dir, "build", "cpp", "Debug")

sys.path.append(module_path)

# Importing out module:
import pyfibonacci


the_answer = pyfibonacci.the_answer
what = pyfibonacci.what


def calc(index: int) -> int:
    if index <= 1:
        return index

    a = 1
    b = 0
    result = 0
    
    for i in range(index - 1):
        result = a + b
        b = a
        a = result

    return result



def calc_externally(index: int) -> int:
    return pyfibonacci.calc(index=index)


class SeriesCalculator:
    def __init__(self) -> None:
        self._indexes = []

    def put_index(self, index: int) -> None:
        self._indexes.append(index)

    def calc(self) -> List[int]:
        result = []
        for index in self._indexes:
            result.append(calc(index=index))
        return result


class ExternalSeriesCalculator:
    def __init__(self) -> None:
        self._calc = pyfibonacci.SeriesCalculator()

    def put_index(self, index: int) -> None:
        self._calc.put_index(index=index)

    def calc(self) -> List[int]:
        return self._calc.calc()
