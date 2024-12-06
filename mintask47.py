from dataclasses import dataclass
from copy import deepcopy


@dataclass
class Node:
    value: int
    prev: int
    size: int


class Stack:
    def __init__(self):
        self.stack = [Node(None, None, 0)]

    def push(self, version, value):
        prev_node = self.stack[version]
        self.stack.append(Node(value, version, prev_node.size + 1))
        return len(self.stack) - 1

    def pop(self, version):
        prev_version = self.stack[version].prev
        if not prev_version:
            self.stack.append(Node(None, None, 0))
        else:
            prev_node = self.stack[prev_version]
            self.stack.append(Node(prev_node.value, prev_node.prev, prev_node.size))
        return len(self.stack) - 1, self.stack[version].value

    def size(self, version):
        return self.stack[version].size


@dataclass
class QueueVersion:
    recopy: bool
    to_copy: int
    copied: bool
    versionR: int  # = [0]
    versionS: int  # = [0]
    versionsL: list  # = [0, 0]
    versionsRc: list  # = [0, 0]
    vL: int  # = 0
    vRc: int  # = 0


class PersistentQueue:
    def __init__(self):
        self.R = Stack()
        self.S = Stack()
        self.L = [Stack(), Stack()]
        self.Rc = [Stack(), Stack()]
        self.versions = [QueueVersion(False, 0, False, 0, 0, [0, 0], [0, 0], 0, 0)]

    def _update_version(self, version):
        prev = self.versions[version]
        self.versions.append(deepcopy(prev))

    def push(self, version, value):
        self._update_version(version)
        current = self.versions[-1]
        if not current.recopy:
            v = self.L[current.vL].push(current.versionsL[current.vL], value)
            current.versionsL[current.vL] = v
            if self.Rc[~current.vRc].size(current.versionsRc[~current.vRc]) > 0:
                v, _ = self.Rc[~current.vRc].pop(current.versionsRc[~current.vRc])
                current.versionsRc[~current.vRc] = v
            self._check_recopy()
        else:
            v = self.L[~current.vL].push(current.versionsL[~current.vL], value)
            current.versionsL[~current.vL] = v
            self._check_normal()

    def pop(self, version):
        self._update_version(version)
        current = self.versions[-1]
        if not current.recopy:
            v, tmp = self.R.pop(current.versionR)
            current.versionR = v
            v, _ = self.Rc[current.vRc].pop(current.versionsRc[current.vRc])
            current.versionsRc[current.vRc] = v
            if self.Rc[~current.vRc].size(current.versionsRc[~current.vRc]) > 0:
                v, _ = self.Rc[~current.vRc].pop(current.versionsRc[~current.vRc])
                current.versionsRc[~current.vRc] = v
            self._check_recopy()
            return tmp
        else:
            v, tmp = self.Rc[current.vRc].pop(current.versionsRc[current.vRc])
            current.versionsRc[current.vRc] = v
            if current.to_copy > 0:
                current.to_copy -= 1
            else:
                v, _ = self.R.pop(current.versionR)
                current.versionR = v
                v, _ = self.Rc[~current.vRc].pop(current.versionsRc[~current.vRc])
                current.versionsRc[~current.vRc] = v
            self._check_normal()
            return tmp

    def _check_recopy(self):
        current = self.versions[-1]
        current.recopy = self.L[current.vL].size(current.versionsL[current.vL]) > self.R.size(current.versionR)
        if current.recopy:
            current.to_copy = self.R.size(current.versionR)
            current.copied = False
            self._check_normal()

    def _check_normal(self):
        self._additional_operations()
        current = self.versions[-1]
        current.recopy = self.S.size(current.versionS) > 0

    def _additional_operations(self):
        current = self.versions[-1]
        to_do = 3
        # from R to S
        while not current.copied and to_do > 0 and self.R.size(current.versionR) > 0:
            v, x = self.R.pop(current.versionR)
            current.versionR = v
            v = self.S.push(current.versionS, x)
            current.versionS = v
            to_do -= 1
        # from L to R and Rc'
        while to_do > 0 and self.L[current.vL].size(current.versionsL[current.vL]) > 0:
            current.copied = True
            v, x = self.L[current.vL].pop(current.versionsL[current.vL])
            current.versionsL[current.vL] = v
            v = self.R.push(current.versionR, x)
            current.versionR = v
            v = self.Rc[~current.vRc].push(current.versionsRc[~current.vRc], x)
            current.versionsRc[~current.vRc] = v
            to_do -= 1
        # from S to R and Rc'
        while to_do > 0 and self.S.size(current.versionS) > 0:
            v, x = self.S.pop(current.versionS)
            current.versionS = v
            if current.to_copy > 0:
                v = self.R.push(current.versionR, x)
                current.versionR = v
                v = self.Rc[~current.vRc].push(current.versionsRc[~current.vRc], x)
                current.versionsRc[~current.vRc] = v
                current.to_copy -= 1
            to_do -= 1
        if self.S.size(current.versionS) == 0:
            current.vL = ~current.vL
            current.vRc = ~current.vRc


def test1():
    pqueue = PersistentQueue()
    for i in range(10):
        pqueue.push(i, i)
    for i in range(10):
        assert i == pqueue.pop(10 + i)


def test2():
    pqueue = PersistentQueue()
    pqueue.push(0, 1)
    pqueue.push(1, 2)
    pqueue.push(0, 3)
    assert 1 == pqueue.pop(2)
    assert 1 == pqueue.pop(2)
    assert 1 == pqueue.pop(1)
    assert 3 == pqueue.pop(3)
    assert 2 == pqueue.pop(4)


if __name__ == "__main__":
    test1()
    test2()
    print()
