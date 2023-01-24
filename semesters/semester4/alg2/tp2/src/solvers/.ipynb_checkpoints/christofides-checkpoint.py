import numpy as np
import networkx as nx

def christofides_tsp(graph):
    best = 0 # path size

    mst = nx.minimum_spanning_tree(graph) # generates the MST for the input graph

    odd_nodes = []
    degrees = nx.degree(mst)

    # stores odd-degree nodes in MST
    for item in degrees:
        node, degree = item

        if degree % 2 != 0:
            odd_nodes.append(node)

    odd_degree_subgraph = nx.subgraph(graph.copy(), odd_nodes) # generate the subgraph for the odd-degree nodes
    edges = list(nx.min_weight_matching(odd_degree_subgraph)) # call the Minimum Weight Matching on the subgraph

    # create and populate the multigraph with all nodes,
    # all edges from the MST and the edges from the Minimum Matching
    multigraph = nx.MultiGraph()

    for i, j, weight in mst.edges(data=True):
        multigraph.add_edge(i, j, weight=weight)

    for edge in edges:
        i, j = edge
        multigraph.add_edge(i, j, weight=odd_degree_subgraph[i][j])

    path = list(nx.dfs_preorder_nodes(multigraph, source=0)) # list the non-repeating nodes in the DFS path
    path.append(path[0]) # insert the start node at the end

    for i in range(len(path) - 1):
        best += graph[path[i]][path[i + 1]]['weight'] # sum the distances of the edges

    return path, best
