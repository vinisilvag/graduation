import numpy as np
import networkx as nx

def tat_tsp(graph):
    best = 0 # path size

    mst = nx.minimum_spanning_tree(graph) # generates the MST for the input graph

    path = list(nx.dfs_preorder_nodes(mst, source=0)) # list the non-repeating nodes in the DFS path
    path.append(path[0]) # insert the start node at the end

    for i in range(len(path) - 1):
        best += graph[path[i]][path[i + 1]]['weight'] # sum the distances of the edges

    return path, best
