```cpp
// Task 1
#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b;
}
```

```cpp
// Task 2
#include <iostream>
#include <vector>
#include <algorithm> // для std::sort

int main() {
    int K;
    std::cin >> K;
    std::vector<int> numbers(K);

    for (int i = 0; i < K; ++i) {
        std::cin >> numbers[i];
    }

    std::sort(numbers.begin(), numbers.end());

    for (int i = 0; i < K; ++i) {
        std::cout << numbers[i] << " ";
    }

    std::cout << std::endl;
    return 0;
}
```

```cpp
// Task 3
#include <iostream>

int main() {
    int n;
    std::cin >> n;

    if (n == 0) {
        std::cout << 0 << std::endl;
    } else if (n == 1) {
        std::cout << 1 << std::endl;
    } else {
        long long a = 0, b = 1, c;
        for (int i = 2; i <= n; ++i) {
            c = a + b;
            a = b;
            b = c;
        }
        std::cout << b << std::endl;
    }

    return 0;
}
```

```cpp
// RE
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};
    std::cout << v.at(10) << std::endl;
    return 0;
}
```

```cpp
//CR
#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b // Нет “;”
    std::cout << a + b
}
```

```cpp
// TL
#include <iostream>

int main() {
    while (true) {
        std::cout << 123;
    }
}
```

```cpp
// Task 1 1st test OK
#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << 134540;
}
```