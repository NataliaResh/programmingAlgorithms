class Node:
    def __init__(self, alive_count, value, left, right):
        self.alive_count = alive_count
        self.value = value
        self.left = left
        self.right = right


def get_alive_count(node: Node):
    if not node:
        return 0
    return node.alive_count


class Tree:
    def __init__(self, array):
        self.array = array
        self.roots = [self._build_zero_version(0, len(array) - 1)]
        self.array = [(array[i], i + 1) for i in range(len(array))]
        self.array.sort(key=lambda x: x[0], reverse=True)
        for i in range(len(array)):
            index = self.array[i][1]
            self.roots.append(self._build_new_version(self.roots[i], index - 1, 0, len(array) - 1))

    def _build_zero_version(self, tl, tr):
        if tl == tr:
            return Node(0, self.array[tl], None, None)
        tm = (tl + tr) >> 1
        left = self._build_zero_version(tl, tm)
        right = self._build_zero_version(tm + 1, tr)
        return Node(0, 0, left, right)

    def _build_new_version(self, root: Node, index, tl, tr):
        if tl == tr:
            return Node(root.alive_count + 1, root.value, root.left, root.right)
        tm = (tl + tr) >> 1
        if index <= tm:
            left = self._build_new_version(root.left, index, tl, tm)
            return Node(left.alive_count + get_alive_count(root.right), root.value, left, root.right)
        right = self._build_new_version(root.right, index, tm + 1, tr)
        return Node(right.alive_count + get_alive_count(root.left), root.value, root.left, right)

    def _sum_alive(self, root, tl, tr, l, r):
        if l == tl and r == tr:
            return root.alive_count
        tm = (tl + tr) >> 1
        sum = 0
        if l <= tm:
            sum += self._sum_alive(root.left, tl, tm, l, min(r, tm))
        if r >= tm + 1:
            sum += self._sum_alive(root.right, tm + 1, tr, max(l, tm + 1), r)
        return sum

    def _find_version(self, k):
        l = -1
        r = len(self.array)
        while l < r - 1:
            m = (l + r) >> 1
            if self.array[m][0] >= k:
                l = m
            else:
                r = m
        return l

    def gte(self, l, r, k):
        version = self._find_version(k)
        # if version == -1 return 0
        return self._sum_alive(self.roots[version + 1], 0, len(self.array) - 1, l, r)


if __name__ == "__main__":
    array1 = Tree([46, 11, 40, 8, 2, 42, 65, 10])
    assert array1.gte(0, 0, 10) == 1
    assert array1.gte(0, 7, 10) == 6
    assert array1.gte(2, 5, 1) == 4
    assert array1.gte(2, 5, 100) == 0

    array2 = Tree([46, 11, 40, 8, 2, 42, 65, 10, 4, 100])
    assert array2.gte(0, 9, 30) == 5
    assert array2.gte(0, 7, 10) == 6
    assert array2.gte(2, 6, 100) == 0
    assert array2.gte(1, 5, 10) == 3