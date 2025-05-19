import os
import random

def write_test_files(folder, inputs_outputs):
    os.makedirs(folder, exist_ok=True)
    for idx, (inp, out) in enumerate(inputs_outputs, start=1):
        with open(os.path.join(folder, f"input{idx}.txt"), "w") as f_in:
            f_in.write(inp)
        with open(os.path.join(folder, f"output{idx}.txt"), "w") as f_out:
            f_out.write(out)

def generate_sum_tests(n=25):
    tests = []
    for _ in range(n):
        a = random.randint(-100000, 100000)
        b = random.randint(-100000, 100000)
        tests.append((f"{a} {b}", f"{a + b}"))
    return tests

def generate_sort_tests(n=25):
    tests = []
    for _ in range(n):
        size = random.randint(5, 150)
        arr = [random.randint(-1000, 1000) for _ in range(size)]
        input_str = f"{size}\n{' '.join(map(str, arr))}"
        output_str = f"{' '.join(map(str, sorted(arr)))}"
        tests.append((input_str, output_str))
    return tests

def generate_fib_tests(n=25):
    def fib(k):
        a, b = 0, 1
        for _ in range(k):
            a, b = b, a + b
        return a

    tests = []
    for _ in range(n):
        k = random.randint(0, 90)
        tests.append((f"{k}", f"{fib(k)}"))
    return tests

def main():
    base_dir = "tests"
    write_test_files(os.path.join(base_dir, "tests_1"), generate_sum_tests())
    write_test_files(os.path.join(base_dir, "tests_2"), generate_sort_tests())
    write_test_files(os.path.join(base_dir, "tests_3"), generate_fib_tests())
    print("Тесты сгенерированы в папке 'tests/'")

if __name__ == "__main__":
    main()