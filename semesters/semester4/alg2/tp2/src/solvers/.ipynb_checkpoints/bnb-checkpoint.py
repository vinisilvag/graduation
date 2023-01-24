import numpy as np
import networkx as nx
from queue import PriorityQueue

import sys

def bnb_tsp(graph, n):
    # root = (...)
    queue = PriorityQueue()
    best = sys.maxsize # infinity
    solution = [] # vertices order

    # queue.put(root)

    while not queue.empty():
        node = queue.get()

    return solution, best
