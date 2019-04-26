import numpy as np
import matplotlib as plt

LIM = 1000000
cant = {}
with(open(INFILE)) as f:
  for (e,line) in enumerate(f):
    data = [int(x) for x in line.strip().split(" ")]
    viaje = data[5] - data[4]
    cant[viaje] += 1
    
