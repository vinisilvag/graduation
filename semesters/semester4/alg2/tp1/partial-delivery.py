# Grupo:
# Vinicius Silva Gomes - 2021421869
# Mirna Mendonça e Silva - 2021421940
# Daniel Barreto Torres - 2018432952

# A implementação da Red-Black Tree ocorre em outro arquivo, que nós importamos no nosso Notebook para usar. Aqui ele foi omitido, mas será entregue junto com o Notebook na entrega final do TP, com os devidos créditos ao criador do código.

## Funções Auxiliares

# Posição relativa do segmento pr em relação ao segmento pq
def relative_position(p, q, r):
    # Produto vetorial dos segmentos pq e pr
    pos = ((r.x - q.x) * (q.y - p.y)) - ((r.y - q.y) * (q.x - p.x))
    
    if pos == 0:
        return 0 # colinear
    elif pos > 0:
        return 1 # sentido horário
    else:
        return -1 # sentido antihorário

# Envoltória Convexa
def find_minor_point(points):
    index = -1
    min_y = sys.maxsize
    
    for idx, point in enumerate(points):
        if point.y < min_y:
            index = idx
            min_y = point.y
        elif point.y == min_y:
            if point.x < points[index].x:
                index = idx
                
    return (points[index], index)

def euclidean_distance(p1, p2):
    distance = sqrt(((p1.x - p2.x) ** 2) + ((p1.y - p2.y) ** 2))
    
    return distance
    
def polar_sort(p0, p1, p2):
    relative_pos = relative_position(p0, p1, p2)
    
    if relative_pos == 0:
        if euclidean_distance(p0, p1) < euclidean_distance(p0, p2):
            return -1
        else:
            return 1
    else:
        return relative_pos
    
def remove_same_polar_angle(points):
    n = len(points)
    remove = []
    
    for i in range(1, n - 1):
        if relative_position(points[0], points[i], points[i+1]) == 0:
            size_seg_a = euclidean_distance(points[0], points[i])
            size_seg_b = euclidean_distance(points[0], points[i+1])
            
            if size_seg_a < size_seg_b:
                remove.append(points[i])
            else:
                remove.append(points[i+1])
                
    for coord in remove:
        if coord in points:
            points.remove(coord)
        
    return points
    
def next_to_top(hull):
    return hull[-2]

def top(hull):
    return hull[-1]

# Varredura linear
def create_events_list(hull):
    events = [];
    
    for i in range(0, len(hull)-1, 2):
        start = Event(hull[i], hull[i+1], True)
        end = Event(hull[i+1], hull[i], False)
        
        events.append(start)
        events.append(end)
        
    return events

def compare_points(p1, p2):
    if p1.x < p2.x:
        return -1
    elif p1.x > p2.x:
        return 1
    
    if p1.x == p2.x:
        if p1.start == p2.start:
            if p1.y < p2.y:
                return -1
            else:
                return 1
            
        if p1.start == True:
            return -1
        else:
            return 1

# Verifica se um ponto está contido dentro de um segmento
def on_segment(p, q, r):
    if r.x >= min(p.x, q.x) and r.x <= max(p.x, q.x):
        if r.y >= min(p.y, q.y) and r.y <= max(p.y, q.y):
            return True
    
    return False

# Verifica se dois segmentos se intersectam
def segments_intersect(p1, p2, p3, p4):
    d1 = relative_position(p3, p4, p1)
    d2 = relative_position(p3, p4, p2)
    d3 = relative_position(p1, p2, p3)
    d4 = relative_position(p1, p2, p4)
    
    if ((d1 > 0 and d2 < 0) or (d1 < 0 and d2 > 0)) and ((d3 > 0 and d4 < 0) or (d3 < 0 and d4 > 0)):
        return True
    elif d1 == 0 and on_segment(p3, p4, p1):
        return True
    elif d2 == 0 and on_segment(p3, p4, p2):
        return True
    elif d3 == 0 and on_segment(p1, p2, p3):
        return True
    elif d4 == 0 and on_segment(p1, p2, p4):
        return True
    else:
        return False

## Funções Principais

# Calcula a envoltória convexa para o conjunto de pontos dados
def graham_scan(points):
    # Encontra p0 no conjunto de dados
    p0, idx = find_minor_point(points)
    
    # Troca o p0 de lugar elemento de índice 0 do conjunto
    aux = points[0]
    points[0] = p0
    points[idx] = aux    
    
    # Ordena os elementos restantes a partir da coordenada polar com relação ao elemento p0
    sorted_points = points.copy()
    sorted_points[1:] = sorted(points[1:], key=cmp_to_key(lambda p1, p2: polar_sort(p0, p1, p2)))
    
    # Remove os pontos que possuem o mesmo ângulo polar em relação a p0 (mantém o que está mais longe)
    sorted_points = remove_same_polar_angle(sorted_points.copy())
    
    if(len(sorted_points) < 3):
        print("É impossível montar uma envoltória convexa com o conjunto de pontos fornecido!")
        return
    
    hull = []
    hull.append(sorted_points[0])
    hull.append(sorted_points[1])
    hull.append(sorted_points[2])
    
    for i in range(3, len(sorted_points)):
        while ((len(hull) > 1) and (relative_position(next_to_top(hull), top(hull), sorted_points[i]) != -1)):
            hull.pop()
            
        hull.append(sorted_points[i])
    
    return hull
    
# Algoritmo da varredura linear para detectar interseção entre um conjunto de pontos
def line_sweep_intersection(events):    
    tree = RedBlackTree()
    
    for event in events:
        tree.insert(event)
        
        predecessor = tree.predecessor(event)
        
        if predecessor and segments_intersect(event.start, event.end, predecessor.start, predecessor.end):
            return True
        
        successor = tree.successor(event)
        
        if successor and segments_intersect(event.start, event.end, successor.start, successor.end):
            return True
        if predecessor and successor:
            if segments_intersect(predecessor.start, predecessor.end, successor.start, successor.end):
                return True
        tree.delete(event)
        
    return False
    
# Algoritmo para verificar se dois conjuntos de pontos são linearmente separável
def hulls_are_linearly_separable(hull_a, hull_b):
    events = create_events_list(hull_a) + create_events_list(hull_b)
    
    events = sorted(events, key=cmp_to_key(lambda p1, p2: compare_points(p1, p2)))
        
    has_intersection = line_sweep_intersection(events)
    
    if has_intersection:
        return False
    else:
        return True
