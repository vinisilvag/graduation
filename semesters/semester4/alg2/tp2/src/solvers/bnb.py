import numpy as np
import networkx as nx
from queue import PriorityQueue

from math import ceil

import sys

# calculate bound for a partial solution
def bound(weights, solution, no_nodes):
    selected = {} # dictionary with the nodes in the graph

    for i in range(no_nodes):
        selected[i] = {} # create dictionary with all nodes in the graph

    copy = weights.copy()
    copy.astype(int)

    # insert the fixed edges from the partial solution
    for i in range(len(solution) - 1):
        start = solution[i]
        end = solution[i + 1]

        # insert fixed edges in the dictionary
        selected[start].update({ end: copy[start][end] })
        selected[end].update({ start: copy[end][start] })

        # makes the inserted edge maxsize so that the next step is unable to select it
        copy[start][end] = sys.maxsize

    # insert edges in each node with less than 2 fixed edges by the partial solution
    for key in selected:
        if len(selected[key].keys()) == 2: continue

        # find the minimum edges incident to the current key and
        # select it until key has 2 edges selected
        while len(selected[key].keys()) < 2:
            minimal = sys.maxsize
            minimal_idx = -1

            for i, w in enumerate(copy[key]):
                if w == 0: continue

                if w < minimal:
                    minimal = w
                    minimal_idx = i

            # insert edge in the dictionary
            selected[key].update({ minimal_idx: minimal })

            # blocks the possibility of this edge being selected again
            copy[key][minimal_idx] = sys.maxsize

    total = 0

    # sum selected edges
    for start in selected:
        for end in selected[start]:
            total += selected[start][end]

    # calculate the metric
    return ceil(total / 2)

# solve the TSP using the branch and bound strategy
def bnb_tsp(weights, graph):
    no_nodes = graph.number_of_nodes() # number of nodes

    root = (bound(weights, [0], no_nodes), 0, 0, [0]) # bound, level, cost, solution
    queue = PriorityQueue()
    best = sys.maxsize # infinity
    solution = [] # vertices order

    queue.put(root) # initialize the queue

    while not queue.empty():
        partial_bound, level, cost, partial_solution = queue.get() # pop the top

        # if the partial solution is a hamiltonian circuit
        if level + 1 > no_nodes:
            # if the cost of the partial solution is "better" than the current solution
            if best > cost:
                best = cost
                solution = partial_solution

        # partial solution is better than the current one
        elif partial_bound < best:
            # all nodes have not yet been inserted into the solution
            if level + 1 < no_nodes:
                # selects a node that is not in the partial solution
                for k in range(1, no_nodes):
                    if k not in partial_solution:
                        distance = weights[partial_solution[-1]][k]

                        incremented_solution = partial_solution.copy()
                        incremented_solution.append(k)

                        bound_value = bound(weights, incremented_solution, no_nodes)

                        # if it is not an edge to itself and the bound is better than the current solution
                        if distance != 0 and bound_value < best:
                            queue.put((bound_value, level + 1, cost + distance, incremented_solution))
            # all nodes have already been inserted
            else:
                connect_to_source = weights[partial_solution[-1]][0]

                if connect_to_source != 0:
                    # inserts the source node at the end of the path
                    solution_connect_source = partial_solution.copy()
                    solution_connect_source.append(0)
                    best_bound = bound(weights, solution_connect_source, no_nodes)

                    # if the partial solution is better than the current one insert it in the queue
                    if best_bound < best and len(partial_solution) == no_nodes:
                        queue.put((best_bound, level + 1, cost + connect_to_source, solution_connect_source))

    return solution, best
