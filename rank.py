#!/bin/python

import math
import os
import random
import re
import sys


class Car:
    def __init__(self, max, unit):
        self.max = max
        self.unit = unit
    
    def __repr__(self):
        return "Car with the maximum speed of " + self.max  + " " +  self.unit
    pass

class Boat:
    def __init__(self, max):
        self.max = max
        
    def __repr__(self):
        return "Boat with the maximum speed of " + self.max + "knots"
        
    pass


car = Car("123", "km/h")
print(car)