from random import *
from typing import NamedTuple

class Constants(NamedTuple):
    m = 1

CONST = Constants()

def rand(x, y):
    return randrange(x, y)