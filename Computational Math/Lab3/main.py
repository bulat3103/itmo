def trapezoid_method(f, a, b, e, n=4):
    answer = {}
    result = float('inf')
    while True:
        last_result = result
        result = (f(a) + f(b)) / 2
        h = (b - a) / n
        x = a + h
        for i in range(n - 1):
            result += f(x)
            x += h
        result *= h
        if abs(result - last_result) <= e:
            break
        else:
            n *= 2
    answer['result'] = result
    answer['n'] = n
    return answer


def simpson_method(f, a, b, e, n=4):
    answer = {}
    if n % 2 != 0:
        return None
    result = float('inf')
    while True:
        last_result = result
        result = f(a) + f(b)
        h = (b - a) / n
        x = a + h
        for i in range(n - 1):
            yi = f(x)
            if i % 2 == 0:
                result += 4 * yi
            else:
                result += 2 * yi
            x += h
        result *= h / 3
        if abs(result - last_result) <= e:
            break
        else:
            n *= 2
    answer['result'] = result
    answer['n'] = n
    return answer


def rectangle(f, a, b, e, n):
    h = (b - a) / n
    result = f(a)
    x = a + h
    for i in range(n - 1):
        yi = f(x)
        result += yi
        x += h
    result *= h
    print("Результат: ", result)


def getfunc(func_id):
    if func_id == '1':
        return lambda x: x ** 2
    elif func_id == '2':
        return lambda x: 1 / x
    elif func_id == '3':
        return lambda x: x ** 3 - 3 * (x ** 2) + 6 * x - 19
    else:
        return None


def getdata():
    data = {}
    print("Выберите функцию:")
    print(" 1 — x²")
    print(" 2 — 1 / x")
    print(" 3 — x³ - 3x² + 6x - 19")
    func = None
    while True:
        func_id = input("Функция: ")
        if func_id != '1' and func_id != '2' and func_id != '3':
            print("Выберите функцию из списка!")
            continue
        func = getfunc(func_id)
        break
    data['func'] = func
    print("Выберите метод решения:")
    print("1 — Метод трапеций")
    print("2 — Метод Симпсона")
    method = ""
    while True:
        method_id = input("Метод решения: ")
        if method_id == '1':
            method = "trapezoid_method"
            break
        elif method_id == '2':
            method = "simpson_method"
            break
        print("Выберите метод из списка!")
    data['method'] = method
    print("Введите пределы интегрирования")
    a, b = 0, 0
    while True:
        a = float(input("\tЛевая граница интервала: "))
        b = float(input("\tПравая граница интервала: "))
        if a <= b:
            break
    data['a'] = a
    data['b'] = b
    error = None
    while True:
        error = float(input("\tВведите погрешность: "))
        if error > 0:
            break
    data['error'] = error
    return data


def main():
    print("Лабораторная работа №3")
    print("Вариант №18")
    print("Численное интегрирование")
    data = getdata()
    answer = None
    if data['method'] == 'trapezoid_method':
        answer = trapezoid_method(data['func'], data['a'], data['b'], data['error'])
    elif data['method'] == 'simpson_method':
        answer = simpson_method(data['func'], data['a'], data['b'], data['error'])
    print("Результат вычисления.")
    print(f"Значение интеграла: {answer['result']}")
    print(f"Количество разбиений: {answer['n']}")
    print("Результат вычислений методом прямоугольников.")
    rectangle(data['func'], data['a'], data['b'], data['error'], 10)


main()
