import numpy as np
import matplotlib.pyplot as plt
from Lab2.NonLinearSystems import CalculatorSystems


def halfDivision_method(a, b, f, e):
    if f(a) * f(b) > 0:
        print("Уравнение содержит 0 или несколько корней!")
        exit(0)
    n = 0
    table = [['№', 'a', 'b', 'x', 'F(a)', 'F(b)', 'F(x)', '|a-b|']]
    while True:
        x = (a + b) / 2
        table.append([n, a, b, x, f(a), f(b), f(x), abs(a - b)])
        if f(a) * f(x) > 0:
            a = x
        else:
            b = x
        n += 1
        if abs(a - b) <= e or abs(f(x)) < e:
            break
    x = (a + b) / 2
    return x, f(x), n, table


def d(n, x, f, h=0.00000001):
    """ Найти значение производной функции """
    if n <= 0:
        return None
    elif n == 1:
        return (f(x + h) - f(x)) / h

    return (d(n - 1, x + h, f) - d(n - 1, x, f)) / h


def simpleIteration_method(a, b, f, e, maxitr=100):
    log = [['№', 'x_i', 'x_(i+1)', 'g(x_i)', 'f(x_i)', '|x_(i+1) - x_i|']]
    x0 = 0

    def g(g_x):
        return g_x + (-1 / d(1, g_x, f)) * f(g_x)

    if abs(d(1, a, g)) < 1 and abs(d(1, b, g)) < 1:
        if f(a) * d(2, a, f) > 0:
            x0 = a
        elif f(b) * d(2, b, f) > 0:
            x0 = b
    else:
        print("Выберите другой интервал! Не выполняется условие сходимости!")
        exit(0)
    x = g(x0)
    log.append([0, x0, x, g(x0), f(x0), abs(x - x0)])
    itr = 1
    while abs(x - x0) > e and itr < maxitr:
        if d(1, x, g) >= 1:
            return None
        x0, x = x, g(x)
        log.append([itr, x0, x, g(x0), f(x0), abs(x - x0)])
        itr += 1
    return x, f(x), itr, log


def plot(x, y):
    """ Отрисовать график по заданным x и y """
    plt.gcf().canvas.manager.set_window_title("График функции")
    ax = plt.gca()
    ax.spines['left'].set_position('zero')
    ax.spines['bottom'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')
    ax.plot(1, 0, marker=">", ms=5, color='k',
            transform=ax.get_yaxis_transform(), clip_on=False)
    ax.plot(0, 1, marker="^", ms=5, color='k',
            transform=ax.get_xaxis_transform(), clip_on=False)
    plt.plot(x, y)
    plt.show()


def getfunc(num):
    if num == '1':
        return np.linspace(-1, 3, 200), \
               lambda x: -1 * (x ** 3) + 5.67 * (x ** 2) - 7.12 * x + 1.34
    elif num == '2':
        return np.linspace(-3, 2, 200), \
               lambda x: x ** 3 - x + 4
    elif num == '3':
        return np.linspace(-20, 20, 200), \
               lambda x: np.sin(x) + 0.1
    elif num == '4':
        return np.meshgrid(np.linspace(-5, 5, 200), np.linspace(-5, 5, 200)), \
               lambda x, y: x ** 2 + y ** 2 - 4
    elif num == '5':
        return np.meshgrid(np.linspace(-5, 5, 200), np.linspace(-5, 5, 200)), \
               lambda x, y: y - 3 * (x ** 2)
    else:
        return None


def file_read(filename, type_func):
    file = open(filename, 'r')
    data = {}
    try:
        a, b, e = map(float, file.readline().strip().split())
        if a > b:
            a, b = b, a
        elif a == b:
            print("Некорректные данные в файле! 'a' не может равняться 'b'!")
            exit(0)
        data['a'] = a
        data['b'] = b
        if e < 0:
            print("Некорректные данные в файле! Погрешность не может быть отрицательной!")
            exit(0)
        data['e'] = e
    except ValueError:
        print("Границы интервала и погрешность должны быть числами, введенными через пробел!")
        exit(0)
    return data


def nonlinearSingle():
    print("Выберите функцию:")
    print("1: x³ - 2.92x² + 4.435x + 0.791")
    print("2: x³ - x + 4")
    print("3: sin(x) + 0.1")
    type_func = input()
    function_data = getfunc(type_func)
    while function_data is None:
        print("Выберите функцию из списка.")
        function_data = getfunc(input("Функция: "))
    x, function = function_data
    print("Выберите метод решения.")
    print(" 1 - Метод половинного деления")
    print(" 2 - Метод простой итерации")
    method = input()
    while (method != '1') and (method != '2') and (method != '3'):
        print("Выберите метод решения из списка.")
        method = input("Метод решения: ")
    print("Теперь нужно ввести данные для функции (границы интервала/начальное приближение к корню и погрешность"
          " вычисления).\n"
          "Выберите способ ввода: из исходного файла (-) или ввести с клавиатуры (+)")
    type_read = input()
    while type_read != '-' and type_read != '+':
        print("Выберите способ ввода из списка.")
        method = input("Способ ввода: ")
    if type_read == "-":
        data = file_read(input("Введите название файла: "), method)
    else:
        data = keyboard_read(method)
    data['function'] = function
    answer = None
    if method == '1':
        answer = halfDivision_method(data['a'], data['b'], data['function'], data['e'])
    elif method == '2':
        answer = simpleIteration_method(data['a'], data['b'], data['function'], data['e'])
        if answer is None:
            print("Не выполняется условие сходимости!")
            exit(0)
    print("Записать ответ в файл (-) или вывести в консоль (+)?")
    type_write = input()
    if type_write == '+':
        print(f"Корень уравнения: {answer[0]}")
        print(f"Значение функции в корне: {answer[1]}")
        print(f"Число итераций: {answer[2]}")
        logChoice = input("Вывести таблицу трассировки? (+/-)\n")
        if logChoice == '+':
            for j in range(len(answer[3][0])):
                print('%12s' % answer[3][0][j], end='')
            print()
            for i in range(1, len(answer[3])):
                for j in range(len(answer[3][i])):
                    if j == 0:
                        print('%12d' % answer[3][i][j], end='')
                    else:
                        print('%12.3f' % answer[3][i][j], end='')
                print()
    else:
        output = open('output.txt', 'w', encoding='utf-8')
        output.write(f"Корень уравнения: {answer[0]}\n")
        output.write(f"Значение функции в корне: {answer[1]}\n")
        output.write(f"Число итераций: {answer[2]}\n")
        for j in range(len(answer[3][0])):
            output.write('%12s' % answer[3][0][j])
        output.write("\n")
        for i in range(1, len(answer[3])):
            for j in range(len(answer[3][i])):
                output.write('%12.3f' % answer[3][i][j])
            output.write('\n')
        output.close()
    plot(x, function(x))


def nonlinearSystem():
    print("В данной задаче будет рассмотрена система уравнений:")
    print("x² + y² = 4")
    print("y = 3x²")
    try:
        x0 = float(input("Введите начальное приближение x0: "))
        y0 = float(input("Введите начальное приближение y0: "))
        e = float(input("Введите погрешность: "))
        arr1, functionF = getfunc('4')
        arr2, functionG = getfunc('5')
        calculator = CalculatorSystems(x0, y0, e, functionF, functionG)
        calculator.calculate()
        del calculator
    except ValueError:
        print("Начальное приближние и погрешность должны быть числами!")
        exit(0)


def keyboard_read(type_func):
    data = {}
    a = float(input("Введите левую границу интервала: "))
    b = float(input("Введите правую границу интервала: "))
    e = float(input("Введите погрешность: "))
    try:
        if a > b:
            a, b = b, a
        elif a == b:
            print("Некорректные данные! 'a' не может равняться 'b'!")
            exit(0)
        data['a'] = a
        data['b'] = b
        if e < 0:
            print("Некорректные данные! Погрешность не может быть отрицательной!")
            exit(0)
        data['e'] = e
    except ValueError:
        print("Границы интервала и погрешность должны быть числами, введенными через пробел!")
        exit(0)
    return data


def main():
    print("Лабораторная работа №2")
    print("Вариант №18")
    print("Численное решение нелинейных уравнений/систем уравнений")
    print("Что вы хотите решить?:")
    print("1: Уравнение")
    print("2: Систему уравнений")
    type_input = input()
    if type_input == '1':
        nonlinearSingle()
    else:
        nonlinearSystem()


main()
