import io
import os

import mintask09

from formating import format_table

metrics = ["sample mean", "standard deviation", "geometric mean"]
algorithms = ["classic algorithm", "quick algorithm", "strassen algorithm"]

# [[0.238675356346456, 1.56, 2.0], [3.3, 2.9, 3.9], [1, 2, 3]])


def check(test_number: int):
    os.chdir(f"./tests/{test_number}")
    try:
        with open(f"./{test_number}.in", "r", encoding="utf-8") as inp, \
                open(f"./{test_number}.out", "r", encoding="utf-8") as out:

            result_matrix = io.StringIO("")
            result_metrics = {}
            assert mintask09.solution(inp, result_matrix, result_metrics)

            result_matrix.seek(0)
            for expected_line in out:
                real_line = result_matrix.readline()
                assert real_line.strip() == expected_line.strip()

            assert not result_matrix.readline()
    finally:
        os.chdir("../..")


def test1():
    check(1)


def test2():
    check(2)


def test3():
    check(3)


def test4():
    check(4)


def test5():
    check(5)


def test6():
    check(6)


def test7():
    check(7)


def test8():
    check(8)


def test9():
    check(9)


def test10():
    check(10)


def test11():
    check(11)


def test12():
    check(12)
