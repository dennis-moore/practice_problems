# sum up individual digits of a number
def sumOfDigits(num):
    numsum = 0
    for digit in str(num):
        numsum += int(digit)
    return numsum


# return the max possible sum for a number of n digits(assume all digits are 9)
def maxPossibleSum(num):
    return 9*len(str(num))


maxSum = 0  # variable to hold the current largest digit sum
breakLoop = False

for a in range(99, 0, -1):
    for b in range(99, 0, -1):
        num = a ** b  # a^b
        digitSum = sumOfDigits(num)  # get the sum of the digits
        if digitSum > maxSum:
            maxSum = digitSum  # set a new max

        # counting down from 99, I can calculate the max possible digit sum(all digits are 9) and compare that to the
        # current max. If less, I can move on to next iteration
        maxPosSum = maxPossibleSum(num)
        if maxPosSum < maxSum:
            if a == b:  # if a and b are equal, I know i'm done
                breakLoop = True
                break
            else:
                break

    if breakLoop:
        break
