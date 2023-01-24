import numpy as np

from math import sqrt

def euclidean(p, q):
    square_delta_x = (p[0] - q[0]) ** 2
    square_delta_y = (p[1] - q[1]) ** 2

    distance = round(sqrt(square_delta_x + square_delta_y))

    return distance

def manhattan(p, q):
    x = abs(p[0] - q[0])
    y = abs(p[1] - q[1])

    return x + y

def generate():
    for k in range(4, 10 + 1): # 4 to 10 inclusive
        size = pow(2, k)

        entrie_euclidean = np.zeros((size, size), dtype=np.uint16)
        entrie_manhattan = np.zeros((size, size), dtype=np.uint16)

        points = {} # define the points coords
        coords = [] # register the coords already used

        for i in range(size):
            while True: # generate new coords if needed
                x = np.random.randint(1, np.iinfo("uint8").max + 1, size=1) # generate x
                y = np.random.randint(1, np.iinfo("uint8").max + 1, size=1) # generate y
                coord = (x, y)

                if coord not in coords: # if coord not used
                    points[i] = coord # store point coord
                    coords.append(coord) # register that coord is now used

                    break # exit the loop

            for j in range(i): # calculate the distances between i and every j from 0 to i (excluded)
                euclidean_distance = euclidean(coords[i], coords[j])
                manhattan_distance = manhattan(coords[i], coords[j])

                entrie_euclidean[i][j] = euclidean_distance
                entrie_euclidean[j][i] = euclidean_distance

                entrie_manhattan[i][j] = manhattan_distance
                entrie_manhattan[j][i] = manhattan_distance

        file = open(f"../experiments/instances/2^{k}-euclidean.txt", "w")
        np.savetxt(file, entrie_euclidean, fmt="%s")

        file.close()

        file = open(f"../experiments/instances/2^{k}-manhattan.txt", "w")
        np.savetxt(file, entrie_manhattan, fmt="%s")

        file.close()

        print(f"Instance 2^{k} created")

def main():
    generate()

if __name__ == "__main__":
    main()
