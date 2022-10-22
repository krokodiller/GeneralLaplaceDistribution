import matplotlib as mpl
import matplotlib.pyplot as plt
import math
import scipy.stats as stats
import scipy.integrate as integrate
import numpy as np
from scipy.misc import derivative
mpl.use('TkAgg')  # or can use 'TkAgg', whatever you have/prefer
a = []
b = []
random = []
L = 1
T = 0

def trunc_mean(x, a):
    retV = 1 / (1 - 2 * a)
    ret = []
    k = find_quantile(a)
    for e in x:
        if (e-T)/L <= -k:
            ret.append(retV * -k)
        elif np.abs((e-T)/L) <= k:
            ret.append(retV * (e-T)/L)
        elif (e-T)/L >= k:
            ret.append(retV * k)
    return ret

def find_quantile(a):
    for n in np.arange(0, 5, 0.01):
        if integrate.quad(lambda x: laplace(x), -np.inf, n)[0] > 1 - a:
            return n

def laplace(x):
    ret = np.exp(-np.abs(x)) / 16
    ret = ret * (pow(np.abs(x), 2) + 3 * np.abs(x) + 3)
    return ret

def low_radical(x, d):
    ret = pow(derivative(laplace, (x-T)/L), 2) * pow(laplace((x-T)/L), d-1)
    return ret

def radical(x, d):
    ret = -L * derivative(laplace, (x-T)/L) * pow(laplace((x-T)/L), d-1)
    ret = ret / integrate.quad(lambda x: low_radical(x, d), -100, 100)[0]
    return ret

def low_lse(x):
    ret = pow(derivative(laplace, (x-T)/L), 2) / laplace((x-T)/L)
    return ret

def lse(x):
    ret = -L * derivative(laplace, (x-T)/L) / laplace((x-T)/L)
    ret = ret / integrate.quad(lambda x: low_lse(x), -100, 100)[0]
    return ret



graphs = ["density+accurate random histogram", "density+distorted random histogram", "accurate random", "distorted random", "influence1", "influence2", "influence3"]
for gr in graphs:
    print("[" + str(graphs.index(gr)) + "] " + gr)

graph = graphs[int(input())]
#graph = graphs[4]

if graph == "density+accurate random histogram":
    f = open("density.txt")
    for line in f:
        data = line.split(" ")
        a.append(float(data[0]))
        b.append(float(data[1].strip("\n")))
    f.close()

    r = open("random.txt")
    for line in r:
        if math.isinf(float(line)):
            continue
        if math.isnan(float(line)):
            continue
        random.append(float(line))
    r.close()
    density = stats.gaussian_kde(random)
    x = np.arange(-10., 10, .01)
    plt.plot(x, density(x), 'C0--', zorder=10)
    plt.plot(a, b, 'C1-')
    plt.title("Density and Accurate random values")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend(['Accurate random values', 'Density'])
    plt.xlim(-10, 10)
    plt.show()
elif graph == "density+distorted random histogram":
    distortionA = []
    distortionB = []
    f = open("density.txt")
    for line in f:
        data = line.split(" ")
        a.append(float(data[0]))
        b.append(float(data[1].strip("\n")))
    f.close()

    r = open("distRandom.txt")
    for line in r:
        if math.isinf(float(line)):
            continue
        if math.isnan(float(line)):
            continue
        random.append(float(line))
    r.close()

    d = open("distortionDensity.txt")
    for line in d:
        data = line.split(" ")
        distortionA.append(float(data[0]))
        distortionB.append(float(data[1].strip("\n")))
    d.close()

    density = stats.gaussian_kde(random)
    x = np.arange(-10., 10, .01)
    plt.plot(x, density(x), 'C0--')
    plt.plot(distortionA, distortionB, 'C3:')
    plt.plot(a, b, 'C1-')
    plt.title("Densities and Distorted random values")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend(['Distorted random values', 'Distorting density', 'Density'])
    plt.xlim(-10, 10)
    plt.show()
elif graph ==  "accurate random":
    r = open("random.txt")
    for line in r:
        if math.isinf(float(line)):
            continue
        if math.isnan(float(line)):
            continue
        random.append(float(line))
    r.close()

    plt.plot(random, u'm.', markersize=1)
    plt.show()
elif graph ==  "distorted random":
    r = open("distRandom.txt")
    for line in r:
        if math.isinf(float(line)):
            continue
        if math.isnan(float(line)):
            continue
        random.append(float(line))
    r.close()

    plt.plot(random, u'm.', markersize=1)
    plt.show()
elif graph == "influence1":
    x = np.arange(-10., 10, .01)
    plt.xlim(-10, 10)
    plt.ylim(-6,6)
    plt.grid(True)
    plt.title("Функции влияния")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.plot(x, x - T)
    plt.plot(x, L * np.sign(x - T) / (2 * laplace(0)))
    plt.plot(x, lse(x))
    plt.legend(['Среднее арифмитическое', 'Выборочная медиана', 'Оценка максимального правдоподобия'])
    plt.show()
elif graph == "influence2":
    x = np.arange(-10., 10, .01)
    plt.xlim(-10, 10)
    plt.ylim(-6,6)
    plt.grid(True)
    plt.title("Функции влияния")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.plot(x, trunc_mean(x, 0.05))
    plt.plot(x, trunc_mean(x, 0.1))
    plt.plot(x, trunc_mean(x, 0.15))
    plt.legend(['Усечённое среднее (0.05)', 'Усечённое среднее (0.10)', 'Усечённое среднее (0.15)'])
    plt.show()
elif graph == "influence3":
    x = np.arange(-10., 10, .01)
    plt.xlim(-10, 10)
    plt.ylim(-6,6)
    plt.grid(True)
    plt.title("Функции влияния")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.plot(x, radical(x, 0.1))
    plt.plot(x, radical(x, 0.5))
    plt.plot(x, radical(x, 1))
    plt.legend(['Обобщённые радикальные оценки (0.1)', 'Обобщённые радикальные оценки (0.5)', 'Обобщённые радикальные оценки (1.0)'])
    plt.show()