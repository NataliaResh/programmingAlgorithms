class UnionFind:
    def __init__(self, n):
        self.n = n
        self.size = 0
        self.set_elements = [-1 for _ in range(n)]
        self.parents = [i for i in range(n)]
        self.rangs = [0 for _ in range(n)]
        self.left_children = [i for i in range(n)]

    def append(self, number, deadline):
        self.size += 1
        repr = self.find(deadline)
        index = self.left_children[repr]
        self.set_elements[index] = number
        if self.size == self.n:
            return
        self.union(repr, index)
        index = (self.n + index - 1) % self.n
        while self.set_elements[index] != -1:
            new_index = self.left_children[self.find(index)]
            self.union(repr, index)
            index = new_index
        self.left_children[self.find(repr)] = index

    def find(self, task):
        if self.parents[task] != task:
            self.parents[task] = self.find(self.parents[task])
        return self.parents[task]

    def union(self, task1, task2):
        repr1 = self.find(task1)
        repr2 = self.find(task2)
        if self.rangs[repr1] >= self.rangs[repr2]:
            self.parents[repr2] = repr1
            if self.rangs[repr1] == self.rangs[repr2]:
                self.rangs[repr1] += 1
        else:
            self.parents[repr1] = repr2

    def get_set_elements(self):
        return self.set_elements


def solution(data: str) -> list:
    data = data.split("\n")
    n = int(data[0])
    union_find = UnionFind(n)
    for i in range(1, n + 1):
        number, deadline, fine = map(int, data[i].split())
        union_find.append(number, deadline)
    return union_find.set_elements
