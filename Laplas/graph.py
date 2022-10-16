import matplotlib as mpl
import matplotlib.pyplot as plt
import math
import scipy.stats as stats
mpl.use('TkAgg')  # or can use 'TkAgg', whatever you have/prefer
a = []
b = []
random = []

graphs = ["density+accurate random histogram", "density+distorted random histogram", "accurate random", "distorted random"]
for gr in graphs:
    print("[" + str(graphs.index(gr)) + "] " + gr)

graph = graphs[int(input())]

match graph:
    case "density+accurate random histogram":
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

        plt.hist(random, density=True, bins=int(len(random) / (len(random) / 100)), histtype=u'step')
        plt.plot(a, b)
        plt.title("Density and Accurate random values")
        plt.xlabel("x")
        plt.ylabel("y")
        plt.legend(['Accurate random values', 'Density'])
        plt.show()
    case "density+distorted random histogram":
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

        plt.hist(random, density=True, bins=int(len(random) / (len(random) / 100)), histtype=u'step')
        plt.plot(a, b)
        plt.title("Density and Distorted random values")
        plt.xlabel("x")
        plt.ylabel("y")
        plt.legend(['Distorted random values', 'Density'])
        plt.show()
    case "accurate random":
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
    case "distorted random":
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

