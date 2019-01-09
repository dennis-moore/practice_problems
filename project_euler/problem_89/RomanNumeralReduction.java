import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;
import static java.util.Arrays.*;

public class RomanNumeralReduction
{

    private String filePath = "roman.txt";
    private static final List<List<String>> replacementRules =
        asList(
            asList("VIIII", "IX"),
            asList("IIII", "IV"),
            asList("LXXXX", "XC"),
            asList("XXXX", "XL"),
            asList("DCCCC", "CM"),
            asList("CCCC", "CD")
        );

    public RomanNumeralReduction(){}

    public RomanNumeralReduction(String filePath)
    {
        this.filePath = filePath;
    }

    public static void main(String[] args)
    {
        RomanNumeralReduction romanNumeralReduction;
        if(args.length > 0)
        {
            romanNumeralReduction = new RomanNumeralReduction(args[0]);
        }
        else
        {
            romanNumeralReduction = new RomanNumeralReduction();
        }

        try
        {
            System.out.println(romanNumeralReduction.doReduction());
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
    }

    private String minimizeNumeral(String romanNumeral)
    {
        String reducedNumeral = romanNumeral;
        for(List<String> rule : replacementRules)
        {
            reducedNumeral = reducedNumeral.replaceAll(rule.get(0), rule.get(1));
        }
        return reducedNumeral;
    }

    private int doReduction() throws IOException
    {
        int savings = 0;
        try(BufferedReader br = new BufferedReader(new FileReader(this.filePath)))
        {
            String romanNumeral = br.readLine();
            while(romanNumeral != null)
            {
                romanNumeral = romanNumeral.replaceAll(" ", "");
                savings += romanNumeral.length() - minimizeNumeral(romanNumeral).length();
                romanNumeral = br.readLine();
            }
        }

        return savings;
    }
}
