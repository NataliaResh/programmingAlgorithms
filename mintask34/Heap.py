class Heap:
    def __init__(self, n):
        self.keys = []  # weights
        self.values = []  # values[i] = house's number that weight on keys[i]
        self.houses = [-1] * n  # houses[i] = index in values of houses with number i

    def sift_down(self, index):
        size = len(self.keys)
        left = 2 * index + 1
        right = 2 * index + 2
        minimum = index
        if left < size and self.keys[minimum] > self.keys[left]:
            minimum = left
        if right < size and self.keys[minimum] > self.keys[right]:
            minimum = right
        if minimum != index:
            self.swap(index, minimum)
            self.sift_down(minimum)

    def extract_min(self):
        house, weight = self.values[0], self.keys[0]
        self.remove(house)
        return house, weight

    def add(self, house, weight):
        index = self.houses[house]
        if index != -1:
            print(index)
            self.keys[index] = min(weight, self.keys[index])
            self.sift_up(index)
        else:
            self.keys.append(weight)
            self.values.append(house)
            self.houses[house] = len(self.keys) - 1
            self.sift_up(len(self.keys) - 1)

    def sift_up(self, index):
        parent = (index - 1) // 2
        while index > 0 and self.keys[parent] > self.keys[index]:
            self.swap(index, parent)

    def swap(self, i, j):
        swap(self.keys, i, j)
        swap(self.values, i, j)
        swap(self.houses, self.values[i], self.values[j])

    def remove(self, house):
        index = self.houses[house]
        self.swap(index, len(self.keys) - 1)
        self.keys.pop()
        self.values.pop()
        self.houses[house] = -1
        self.sift_up(len(self.keys) - 1)

    def is_empty(self):
        return not self.keys


def swap(array, i, j):
    array[i], array[j] = array[j], array[i]
