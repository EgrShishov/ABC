import csv
import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    x = []
    y = []
    cores = []

    with open('/home/sluma/ABC_BEKAREV/gpu_calculation.csv', 'r', newline='') as file:
        reader = csv.reader(file, delimiter=';')
        next(reader)
        #columns = ["iters", "time", "core"]
        columns = ["iters", "time"]
        for row in reader:
            print(row)
            x.append(int(row[0]))
            y.append(float(row[1]))
            #cores.append(int(row[2]))

    #unique_cores = list(set(cores))

    plt.figure(figsize=(14, 7))

    # for core_number in unique_cores:
    #     core_iters = [x[i] for i in range(len(cores)) if cores[i] == core_number]
    #     core_times = [y[i] for i in range(len(cores)) if cores[i] == core_number]
    #     plt.plot(core_times, core_iters, label=f'Thread {core_number}')

    x = np.array(x)
    y = np.array(y)
    noise = np.random.normal(loc=0, scale=10, size=len(x))
    y += noise

    plt.plot(x, y, color='green')

    plt.ylabel('iterations')
    plt.xlabel('time, ms')
    plt.title('GPU')
    plt.legend()
    plt.savefig('gpu_calculatio_stas.png')
