import io
import sys
from typing import TextIO


def classic_mul_matrix(matrix1, matrix2):
    n = len(matrix1)
    matrix_ans = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                matrix_ans[i][j] += matrix1[i][k] * matrix2[k][j]
    return matrix_ans


def copy_matrix(matrix, n):
    return [[matrix[i][j] for j in range(n)] for i in range(n)]


def sum_matrix(matrix1, matrix2):
    n = len(matrix1)
    ans_matrix = copy_matrix(matrix1, n)
    for i in range(n):
        for j in range(n):
            ans_matrix[i][j] += matrix2[i][j]
    return ans_matrix


def diff_matrix(matrix1, matrix2):
    n = len(matrix1)
    ans_matrix = copy_matrix(matrix1, n)
    for i in range(n):
        for j in range(n):
            ans_matrix[i][j] -= matrix2[i][j]
    return ans_matrix


def min_degree(n):
    ans = 2
    while n > ans:
        ans *= 2
    return ans


def add_zeros_to_matrix(matrix, size):
    n = len(matrix)
    for i in range(n):
        matrix[i] += [0] * (size - n)
    matrix += [[0] * size for _ in range(size - n)]


def preparation_matrix(matrix1, matrix2):
    size = min_degree(len(matrix1))
    add_zeros_to_matrix(matrix1, size)
    add_zeros_to_matrix(matrix2, size)


def get_sub_matrix(matrix):
    n = len(matrix)
    middle = n // 2
    a = [[matrix[i][j] for j in range(middle)] for i in range(middle)]
    b = [[matrix[i][j] for j in range(middle, n)] for i in range(middle)]
    c = [[matrix[i][j] for j in range(middle)] for i in range(middle, n)]
    d = [[matrix[i][j] for j in range(middle, n)] for i in range(middle, n)]
    return a, b, c, d


def create_matrix(part1, part2, part3, part4):
    middle = len(part1)
    n = middle * 2
    ans_matrix = [[0] * n for _ in range(n)]
    for i in range(middle):
        for j in range(middle):
            ans_matrix[i][j] = part1[i][j]
    for i in range(middle):
        for j in range(middle):
            ans_matrix[i][j + middle] = part2[i][j]
    for i in range(middle):
        for j in range(middle):
            ans_matrix[i + middle][j] = part3[i][j]
    for i in range(middle):
        for j in range(middle):
            ans_matrix[i + middle][j + middle] = part4[i][j]
    return ans_matrix


def quick_mul_matrix_imp(matrix1, matrix2):
    n = len(matrix1)
    if n <= 4:
        return classic_mul_matrix(matrix1, matrix2)
    a, b, c, d = get_sub_matrix(matrix1)
    e, f, g, h = get_sub_matrix(matrix2)
    part1 = sum_matrix(quick_mul_matrix_imp(a, e), quick_mul_matrix_imp(b, g))
    part2 = sum_matrix(quick_mul_matrix_imp(a, f), quick_mul_matrix_imp(b, h))
    part3 = sum_matrix(quick_mul_matrix_imp(c, e), quick_mul_matrix_imp(d, g))
    part4 = sum_matrix(quick_mul_matrix_imp(c, f), quick_mul_matrix_imp(d, h))
    return create_matrix(part1, part2, part3, part4)


def quick_mul_matrix(matrix1, matrix2):
    n = len(matrix1)
    preparation_matrix(matrix1, matrix2)
    ans_matrix = quick_mul_matrix_imp(matrix1, matrix2)
    return [[ans_matrix[i][j] for j in range(n)] for i in range(n)]


def strassen_mul_matrix_imp(matrix1, matrix2):
    n = len(matrix1)
    if n <= 4:
        return classic_mul_matrix(matrix1, matrix2)
    a, b, c, d = get_sub_matrix(matrix1)
    e, f, g, h = get_sub_matrix(matrix2)
    p1 = strassen_mul_matrix_imp(a, diff_matrix(f, h))
    p2 = strassen_mul_matrix_imp(sum_matrix(a, b), h)
    p3 = strassen_mul_matrix_imp(sum_matrix(c, d), e)
    p4 = strassen_mul_matrix_imp(d, diff_matrix(g, e))
    p5 = strassen_mul_matrix_imp(sum_matrix(a, d), sum_matrix(e, h))
    p6 = strassen_mul_matrix_imp(diff_matrix(b, d), sum_matrix(g, h))
    p7 = strassen_mul_matrix_imp(diff_matrix(a, c), sum_matrix(e, f))

    q1 = sum_matrix(diff_matrix(sum_matrix(p5, p4), p2), p6)
    q2 = sum_matrix(p1, p2)
    q3 = sum_matrix(p3, p4)
    q4 = diff_matrix(diff_matrix(sum_matrix(p1, p5), p3), p7)
    return create_matrix(q1, q2, q3, q4)


def strassen_mul_matrix(matrix1, matrix2):
    n = len(matrix1)
    preparation_matrix(matrix1, matrix2)
    ans_matrix = strassen_mul_matrix_imp(matrix1, matrix2)
    return [[ans_matrix[i][j] for j in range(n)] for i in range(n)]


def print_matrix(matrix):
    for i in range(len(matrix)):
        print(*matrix[i])


def solution(file_with_mmatrix: TextIO, output: TextIO):
    n = int(file_with_mmatrix.readline().strip())
    matrix1 = []
    for i in range(n):
        matrix1.append(list(map(int, file_with_mmatrix.readline().strip().split())))
    matrix2 = []
    for i in range(n):
        matrix2.append(list(map(int, file_with_mmatrix.readline().strip().split())))

    classic_ans_matrix = classic_mul_matrix(copy_matrix(matrix1, n), copy_matrix(matrix2, n))
    quick_ans_matrix = quick_mul_matrix(copy_matrix(matrix1, n), copy_matrix(matrix2, n))
    strassen_ans_matrix = strassen_mul_matrix(copy_matrix(matrix1, n), copy_matrix(matrix2, n))

    for i in range(n):
        output.write(" ".join(map(str, classic_ans_matrix[i])) + "\n")

    return classic_ans_matrix == quick_ans_matrix == strassen_ans_matrix


if __name__ == '__main__':
    print("$ ", end="")
    t = ""
    for line in sys.stdin:
        if line.strip() == "":
            break
        t += line
    solution(io.StringIO(t), sys.stdout)
    print("$ ", end="")


