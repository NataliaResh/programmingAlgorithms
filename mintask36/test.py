import mintask36

verbose = False


def check(test_number: int):
    with open(f"./tests/{test_number}.in", "r") as inp:
        with open(f"./tests/{test_number}.out", "r") as out:
            data = inp.read()
            out = out.read()
            expected_ans = list(map(int, out.split()))
            if verbose:
                print(f"\nTesting on:\n{data}\nExpected ans: {expected_ans}")

            ans = mintask36.solution(data)
            assert ans == expected_ans


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
