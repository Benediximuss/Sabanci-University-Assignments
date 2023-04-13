import random

# Generates a random farm matrix with given row and column numbers, and every cell has a 1/3 probability to have weed
def generateRandomFarm(row, col):
    farmMatrix = [ [ random.choice(['-','-','x']) for m in range(0, col) ] for n in range(0, row)]
    return farmMatrix

# Visualizes the farm matrix
def printFarm(farmMatrix):
    for i in range(len(farmMatrix)):
        print("|", end='')
        for j in range(len(farmMatrix[i])):
            print("", farmMatrix[i][j], end=' ')
        print("|")
    print()

# Checks if given location has weed or not
def hasWeed(i, j, farmMatrix):
    return 1 if farmMatrix[i][j] == 'x' else 0

# Recursive algorithm to find max weed at given location
def maxWeedNaive(m, n, farmMatrix):
    if m == 0 and n == 0:
        return hasWeed(m, n, farmMatrix)
    elif m == 0:
        return maxWeedNaive(m,n-1,farmMatrix) + hasWeed(m, n, farmMatrix)
    elif n == 0:
        return maxWeedNaive(m-1,n,farmMatrix) + hasWeed(m, n, farmMatrix)
    else:
        return max(maxWeedNaive(m-1,n,farmMatrix), maxWeedNaive(m,n-1,farmMatrix)) + hasWeed(m, n, farmMatrix)

# Dynamic Programming algorithm to find max weed at given location
def maxWeedDynamicProgramming(m, n, farmMatrix):
    dpTable = [ [ hasWeed(i, j, farmMatrix) for j in range(0, n+1) ] for i in range(0, m+1)]

    for i in range(1, n+1):
        dpTable[0][i] += dpTable[0][i-1]

    for i in range(1, m+1):
        dpTable[i][0] += dpTable[i-1][0]

    for i in range(1, m+1):
        for j in range(1, n+1):
            dpTable[i][j] += max(dpTable[i-1][j], dpTable[i][j-1])

    return dpTable[m][n]

    
