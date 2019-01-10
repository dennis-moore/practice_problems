import java.math.BigInteger;

public class PowerfulDigitSum
{

    public static int sumOfDigits(BigInteger num)
    {
        int numsum = 0;
        for(char digit : num.toString().toCharArray())
        {
            numsum += Character.getNumericValue(digit);
        }
        return numsum;
    }

    public static int maxPossibleSum(BigInteger num)
    {
        return 9*num.toString().length();
    }

    public static int findMaxSum()
    {
        BigInteger num = new BigInteger("0");
        int digitSum = 0;
        int maxPosSum = 0;
        int maxSum = 0;

        for(int a = 99; a > 0; a--)
        {
            for(int b = 99; b > 0; b--)
            {
                BigInteger bigA = new BigInteger(Integer.toString(a));
                num = bigA.pow(b);
                digitSum = sumOfDigits(num);
                if(digitSum > maxSum)
                {
                    maxSum = digitSum;
                }

                maxPosSum = maxPossibleSum(num);
                if(maxPosSum < maxSum)
                {
                    if(a == b) { return maxSum; }
                    else { break; }
                }
            }
        }

        return maxSum;
    }

    public static void main(String[] args)
    {
        int result = findMaxSum();
        System.out.println(result);
    }
}
