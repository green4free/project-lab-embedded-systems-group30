
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
import csv

rc('text', usetex=True)


downStrain = []
upStrain = []

downRes = []
upRes = []

with open('theirData.csv') as csv_data:
    i = 0
    csv_reader = csv.reader(csv_data, delimiter=',')
    for row in csv_reader:
        if i < 7:
            downStrain.append(-100.0 * float(row[1]))
            downRes.append(1000.0 * float(row[0]))
        else:
            upStrain.append(-100.0 * float(row[1]))
            upRes.append(1000.0 * float(row[0]))
        i += 1

zeroR = downRes[0]


downRes = np.array(downRes)
upRes = np.array(upRes)

downStrain = np.array(downStrain)
upStrain = np.array(upStrain)


downDRbR = 100.0 * (downRes - zeroR) / zeroR
upDRbR = 100.0 * (upRes - zeroR) / zeroR




print ("Gauge factor: ",1.0 / np.polyfit(np.concatenate((downDRbR,upDRbR)), np.concatenate((downStrain,upStrain)), 1)[0])

plt.plot(downStrain, downDRbR,marker='o', label=r'\LARGE Loading')
plt.plot(upStrain, upDRbR,marker='o', label=r'\LARGE Unloading')

plt.legend(loc='upper left')

plt.xlabel(r'\huge strain$\%$')
plt.ylabel(r'\huge $\frac{\Delta R}{R_0}\%$')


print ("Strain Loading ", downStrain)
print ("deltaR/R Loading", downDRbR)

print ("Strain Unloading ", upStrain)
print ("deltaR/R Unloading", upDRbR)

plt.show()
