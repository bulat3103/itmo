from Lab1.Calculator import Calculator


def input_console():
    print("Введите размерность матрицы 1 < n <= 20:")
    n = int(input().strip())
    if 1 < n <= 20:
        print("Введите уравнения в формате:\n"
              "ai1 ai2 ... aij | bi")
        a = []
        for i in range(n):
            while True:
                row = input().split()
                if len(row) - 2 == n and row[-2] == "|":
                    a.append(row)
                    break
                else:
                    print("Проверьте правильность ввода! Попробуйте еще раз!")
        for i in range(len(a)):
            for j in range(len(a[i])):
                if a[i][j] != "|":
                    a[i][j] = float(a[i][j])
        det = determinant(a)
        if det == 0:
            print("Не имеет решений! Определитель равен 0!")
            return
        print("Детерминант: " + str(det))
        calculator = Calculator(n, a)
        calculator.calculate()
        del calculator
    else:
        print("Неправильное значение!")
        return


def input_file(path):
    n = 0
    a = []
    file = open(path, 'r', encoding='utf-8')
    for line in file:
        if line != "\n" and line != " " and line != " \n":
            n += 1
    file.close()
    file = open(path, 'r', encoding='utf-8')
    for row in file:
        line = row.split()
        if line[-2] == "|" and len(line) - 2 == n:
            a.append(line)
        else:
            print("Неправильное содержимое файла!")
    file.close()
    for i in range(len(a)):
        for j in range(len(a[i])):
            if a[i][j] != "|":
                a[i][j] = float(a[i][j])
    det = determinant(a)
    if det == 0:
        print("Не имеет решений! Определитель равен 0!")
        return
    print("Детерминант: " + str(det))
    calculator = Calculator(n, a)
    calculator.calculate()
    del calculator


def minor(matrix, i, j):
    n = len(matrix)
    return [[matrix[row][col] for col in range(n) if col != j] for row in range(n) if row != i]


def determinant(matrix):
    n = len(matrix)
    if n == 1:
        return matrix[0][0]
    det = 0
    sgn = 1
    for j in range(n):
        det += sgn * matrix[0][j] * determinant(minor(matrix, 0, j))
        sgn *= -1
    return det


def main():
    print("Лабораторная работа #1\n"
          "Метод Гаусса\n"
          "Выберите доступную функциональность:\n"
          "\t1. Ввод с консоли.\n"
          "\t2. Чтение из файла.")
    action_type = input().strip()
    if action_type == "1":
        input_console()
    elif action_type == "2":
        input_file(input("Пропишите путь к файлу:\n").strip())
    else:
        print("Неверный ввод!")


main()
