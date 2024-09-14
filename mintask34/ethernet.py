import Heap


def prima(graph: list, node: int, visited: list) -> int:
    n = len(graph)
    ans = 0
    queue = Heap.Heap(n)
    queue.add(node, 0)
    while not queue.is_empty():
        house, weight = queue.extract_min()
        print(house, weight)
        ans += weight
        visited[house] = 1
        for h, w in graph[house]:
            if not visited[h]:
                queue.add(h, w)
    return ans


def solution(data: str) -> (int, int):
    data = data.split('\n')
    n, m = map(int, data[0].split())
    graph = [[] for _ in range(n)]
    for i in range(m):
        start, finish, weight = map(int, data[i + 1].split())
        graph[start].append((finish, weight))
        graph[finish].append((start, weight))
    visited = [0] * n
    count_points = 0
    cable_len = 0
    for i in range(n):
        if not visited[i]:
            cable_len += prima(graph, i, visited)
            count_points += 1
    return count_points, cable_len
