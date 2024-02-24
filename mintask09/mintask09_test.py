import io
import os

import mintask09

from formating import format_table

benchmarks = ["sample mean", "standard deviation", "geometric mean"]
algorithms = ["classic algorithm", "quick algorithm", "strassen algorithm"]


def check(test_number: int):
    os.chdir(f"./tests/{test_number}")
    try:
        with open(f"./{test_number}.in", "r", encoding="utf-8") as inp, \
                open(f"./{test_number}.out", "r", encoding="utf-8") as out:

            result_matrix = io.StringIO("")
            correct_algos, result_metrics = mintask09.solution(inp, result_matrix)
            assert correct_algos

            result_matrix.seek(0)
            n = 0
            for expected_line in out:
                real_line = result_matrix.readline()
                n += 1
                assert real_line.strip() == expected_line.strip()

            assert not result_matrix.readline()
        with open("../../results", "a", encoding="utf-8") as res:
            res.write(f"Test number: {test_number}. Size of matrix: {n}\n")
            res.write(format_table(benchmarks, algorithms, result_metrics) + "\n")
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
