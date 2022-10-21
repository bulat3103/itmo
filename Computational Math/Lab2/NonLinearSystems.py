import numpy as np
import matplotlib.pyplot as plt


class CalculatorSystems:
    e = 0
    x = 0
    y = 0
    x0 = 0
    y0 = 0
    itr = 0
    f = None
    g = None

    def __init__(self, x0, y0, e, f, g):
        self.x0 = x0
        self.y0 = y0
        self.e = e
        self.f = f
        self.g = g

    def calculate(self):
        while 1 and self.itr < 250000:
            self.x = self.x0 - determinant(
                self.get_a(1, self.x0, self.y0)) / determinant(
                self.jacobian(self.x0, self.y0))
            self.y = self.y0 - determinant(
                self.get_a(2, self.x0, self.y0)) / determinant(
                self.jacobian(self.x0, self.y0))
            self.itr += 1
            if abs(self.x - self.x0) <= self.e and abs(
                    self.y - self.y0) <= self.e:
                break
            self.x0 = self.x
            self.y0 = self.y
        printResult(self)
        plot(self.f, self.g)

    def x_derivative(self, type_eq, x, y, h=0.00001):
        if type_eq == 1:
            return (self.f(x + h, y) - self.f(x, y)) / h
        elif type_eq == 2:
            return (self.g(x + h, y) - self.g(x, y)) / h

    def y_derivative(self, type_eq, x, y, h=0.00001):
        if type_eq == 1:
            return (self.f(x, y + h) - self.f(x, y)) / h
        elif type_eq == 2:
            return (self.g(x, y + h) - self.g(x, y)) / h

    def jacobian(self, x, y):
        return [[self.x_derivative(1, x, y),
                 self.y_derivative(1, x, y)],
                [self.x_derivative(2, x, y),
                 self.y_derivative(2, x, y)]]

    def get_a(self, mode, x, y):
        if mode == 1:
            return [[self.f(x, y),
                     self.y_derivative(1, x, y)],
                    [self.g(x, y),
                     self.y_derivative(2, x, y)]]
        elif mode == 2:
            return [[self.x_derivative(1, x, y),
                     self.f(x, y)],
                    [self.x_derivative(2, x, y),
                     self.g(x, y)]]


def determinant(matrix):
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]


def plot(f, g):
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
    xRange = np.arange(-10, 10, 0.025)
    yRange = np.arange(-10, 10, 0.025)
    X, Y = np.meshgrid(xRange, yRange)
    F = f(X, Y)
    G = g(X, Y)
    plt.contour(X, Y, F, [0])
    plt.contour(X, Y, G, [0])
    plt.show()


def printResult(calculator):
    print("Записать ответ в файл (-) или вывести в консоль (+)?")
    type_write = input()
    if type_write == '+':
        print("Корни: x=" + str(calculator.x) + ", y=" + str(calculator.y) + "\n" +
              "Количество итераций: " + str(calculator.itr) + "\n" +
              "Погрешность: " + str(calculator.e) + "\n")
        print("F(x, y) = ", calculator.f(calculator.x, calculator.y))
        print("G(x, y) = ", calculator.g(calculator.x, calculator.y))
    else:
        output = open('output.txt', 'w', encoding='utf-8')
        output.write("Корни: x=" + str(calculator.x) + ", y=" + str(calculator.y) + "\n" +
                     "Количество итераций: " + str(calculator.itr) + "\n" +
                     "Погрешность: " + str(calculator.e) + "\n")
        output.close()
