import functions as fn

# Black box testing with following test cases
# 'x' = weed, '-' = no weed

testCases = [(1,1), (2,2), (4,4), (5,6), (6,1), (3,7), (2, 9), (12,12)]

for testCase in testCases:
    tempFarm = fn.generateRandomFarm(testCase[0], testCase[1])

    print("Random farm of", str(testCase[0]) + "x" + str(testCase[1]), ":\n")

    fn.printFarm(tempFarm)
    
    print("Naive algorithm returned:", fn.maxWeedNaive(testCase[0] - 1, testCase[1] - 1, tempFarm))
    print("Dynamic programming algorithm returned:", fn.maxWeedDynamicProgramming(testCase[0] - 1, testCase[1] - 1, tempFarm), "\n\n")
