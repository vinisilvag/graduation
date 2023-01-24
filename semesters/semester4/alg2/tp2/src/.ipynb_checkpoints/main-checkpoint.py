import sys
import os

import numpy as np
import networkx as nx

import csv

from timeit import default_timer as timer
from datetime import timedelta

from solvers.bnb import bnb_tsp
from solvers.tat import tat_tsp
from solvers.christofides import christofides_tsp

def main():
    solver = sys.argv[1] # solver function: first argument
    entrie = sys.argv[2] # entrie: second argument
    measure_type = sys.argv[3] # measure type: third argument

    instances_path = '../experiments/instances' # instances path
    output_path = '../experiments/output.csv' # output path

    header = ["solver", "entrie", "metric", "path", "cost", "time", "space"] # csv header

    output_exists = os.path.isfile(output_path) # output file already created
    output = open(output_path, 'a+')
    writer = csv.writer(output)

    if not output_exists:
        writer.writerow(header) # if not created, create and write header

    # load weights matrix
    weights = np.loadtxt(f'{instances_path}/{entrie}-{measure_type}.txt',
                             dtype=np.int16)

    # create and populate graph
    graph = nx.from_numpy_matrix(weights, create_using=nx.Graph())

    if solver == "bnb":
        print("bnb")

    elif solver == "tat":
        start = timer()

        path, best = tat_tsp(graph) # call the Twice-Around-the-Tree solver for the metric TSP

        end = timer()
        time = (end - start) * 1000 # time in milliseconds

        writer.writerow(["twice-around-the-tree",
                         entrie,
                         measure_type,
                         path,
                         best,
                         time,
                         "space"])

    elif solver == "christofides":
        start = timer()

        path, best = christofides_tsp(graph) # call the Christofides algorithm to solve the metric TSP

        end = timer()
        time = (end - start) * 1000 # time in milliseconds

        writer.writerow(["christofides",
                         entrie,
                         measure_type,
                         path,
                         best,
                         time,
                         "space"])

    output.close()

if __name__ == '__main__':
    main()
