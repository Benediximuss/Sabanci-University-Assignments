import functions as fn

import time
import matplotlib.pyplot as plt

# Test the function with random generated NxN matrix each time by increasing N with 10, from N=1 to N=500, for 10 testing at each N to get more accurate average time.
# It takes about 25-30 seconds to complete the test for current setup.

sizeStart = 1
sizeRange = 500
sizeStep = 10
testingCount = 10

sizesListDP = list()
timesListDP = list()

for testSize in range(sizeStart, sizeRange, sizeStep):
    timeSum = 0
    for test in range(testingCount):
        tempFarm = fn.generateRandomFarm(testSize, testSize)
        startTime = time.time()
        result = fn.maxWeedDynamicProgramming(testSize-1, testSize-1, tempFarm)
        endTime = time.time()
        timeSum += endTime - startTime
    sizesListDP.append(testSize)
    timesListDP.append(timeSum/testingCount)

plt.figure(figsize =(7.5, 5.5))
plt.title('Running Times of Dynamic Programming Algorithm')
plt.xlabel('Test Size (N)')
plt.ylabel('Average Time for NxN farm (sec)')
plt.plot(sizesListDP, timesListDP, color="Brown")
plt.show()
