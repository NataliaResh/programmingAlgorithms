import os
from random import randint


def classic_mul_matrix(matrix1, matrix2):
    n = len(matrix1)
    matrix_ans = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                matrix_ans[i][j] += matrix1[i][k] * matrix2[k][j]
    return matrix_ans


def random_matrix(n):
    return [[randint(-20, 20) for i in range(n)] for j in range(n)]


def generate(test_number):
    n = randint(10, 1000)
    matrix1 = random_matrix(n)
    matrix2 = random_matrix(n)
    os.mkdir(f"{test_number}")
    os.chdir(f"{test_number}")
    with open(f"{test_number}.in", "w", encoding="utf-8") as inp:
        inp.write(f"{n}\n")
        for i in range(n):
            inp.write(" ".join(map(str, matrix1[i])) + "\n")
        for i in range(n):
            inp.write(" ".join(map(str, matrix2[i])) + "\n")
    ans_matrix = classic_mul_matrix(matrix1, matrix2)
    with open(f"{test_number}.out", "w", encoding="utf-8") as out:
        for i in range(n):
            out.write(" ".join(map(str, ans_matrix[i])) + "\n")
    os.chdir("../")


for i in range(3, 13):
    generate(i)
