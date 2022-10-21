class Calculator:
    n = 0
    system = []
    x = []

    def __init__(self, n, system):
        self.n = n
        self.system = system
        self.x = []

    def calculate(self):
        try:
            print("Исходная система:")
            self.print_system()
            self.triangle()
            self.determinant()
            print("Треугольная система:")
            self.print_system()
            self.solution()
            self.print_x()
            self.get_residuals()
        except ArithmeticError:
            return

    def print_x(self):
        print("Решение:")
        for i in range(self.n):
            print("\tX_" + str(i + 1) + " = " + str(self.x[self.n - i - 1]))

    def solution(self):
        self.x.append(self.system[self.n - 1][-1] / self.system[self.n - 1][self.n - 1])
        for i in range(self.n - 2, -1, -1):
            value = self.system[i][-1]
            k = self.n - 1
            while k > i:
                value -= self.x[self.n - 1 - k] * self.system[i][k]
                k -= 1
            self.x.append(value / self.system[i][i])

    def check_diagonal(self, i):
        j = i
        while j < self.n:
            if self.system[j][i] != 0 and self.system[i][j] != 0:
                swap = self.system[j]
                self.system[j] = self.system[i]
                self.system[i] = swap
                return
            j += 1
        print("Нет решений!")
        return ArithmeticError

    def print_system(self):
        for i in range(self.n):
            for j in range(self.n):
                print(str(self.system[i][j]) + " x_" + str(j + 1) + " ", end='')
            print(str(self.system[i][-2]) + " " + str(self.system[i][-1]), end='')
            print("")

    def determinant(self):
        det = 1
        for i in range(self.n):
            det *= self.system[i][i]
        if det == 0:
            print("Определитель равен 0! Нет решений!")
            return ArithmeticError
        print("определитель равен: " + str(det))

    def triangle(self):
        try:
            for i in range(self.n):
                if self.system[i][i] == 0:
                    self.check_diagonal(i)
                m = i
                while m < self.n - 1:
                    a = -(self.system[m + 1][i] / self.system[i][i])
                    j = i
                    while j < self.n:
                        self.system[m + 1][j] += a * self.system[i][j]
                        j += 1
                    self.system[m + 1][-1] += a * self.system[i][-1]
                    m += 1
                k, check = 0, False
                while k < self.n:
                    if self.system[i][k] != 0:
                        check = True
                        break
                    k += 1
                if not check:
                    print("Нет решений! Определитель равен 0!")
                    return ArithmeticError
        except ValueError:
            print("Неправильные данные!")
            return

    def get_residuals(self):
        i = 0
        print("Вектора невязок:")
        self.x.reverse()
        while i < self.n:
            res = 0
            j = 0
            while j < self.n:
                res += self.system[i][j] * self.x[j]
                j += 1
            res -= self.system[i][-1]
            i += 1
            print("\tВектор невязок для № %d = %.20f" % (i, abs(res)))
        print("")
