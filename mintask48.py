from itertools import permutations, combinations
from time import time


def simple_solution(graph, n):
    if n < 2:
        return 0
    nodes = range(n)
    permutations_nodes = list(permutations(nodes))
    ans = float("inf")
    for permutation in permutations_nodes:
        current_len = 0
        for i in range(1, n):
            node_from = permutation[i]
            node_to = permutation[i - 1]
            current_len += graph[node_from][node_to]
        current_len += graph[permutation[-1]][permutation[0]]
        ans = min(ans, current_len)
    return ans


def set_to_bitmask(nodes: set):
    ans = 0
    for i in nodes:
        ans += 1 << i
    return ans


def solution(graph, n):
    if n < 2:
        return 0
    count_sets = (1 << n)
    a = [[float("inf") for _ in range(count_sets)] for _ in range(n)]
    a[0][1] = 0

    nodes = range(n)
    for m in range(2, n + 1):
        combinations_nodes = filter(lambda x: 0 in x, list(combinations(nodes, m)))
        for combination in combinations_nodes:
            combination = set(combination)
            s = set_to_bitmask(combination)
            for v in combination:
                if v == 0:
                    continue
                for w in combination:
                    if w == v:
                        continue
                    a[v][s] = min(a[v][s], a[w][set_to_bitmask(combination - {v})] + graph[v][w])
    ans = float("inf")
    for v in range(1, n):
        ans = min(ans, a[v][count_sets - 1] + graph[v][0])
    return ans


def build_graph(n):
    graph = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            graph[i][j] = i + j + 1
    return graph


def solution_with_time(graph, n):
    start_time = time()
    solution(graph, n)
    end_time = time()
    print("Bellman solution: n =", n, "time =", end_time - start_time)

if __name__ == "__main__":
    for n in range(1, 10):
        graph = build_graph(n)
        assert simple_solution(graph, n) == solution(graph, n)
    n = 10
    graph = build_graph(n)
    print("For size:", n)
    start_time = time()
    ans1 = simple_solution(graph, n)
    end_time = time()
    print("Simple solution:", end_time - start_time)
    start_time = time()
    ans2 = solution(graph, n)
    end_time = time()
    print("Bellman solution:", end_time - start_time)
    assert ans1 == ans2
    for n in range(11, 25):
        graph = build_graph(n)
        solution_with_time(graph, n)

