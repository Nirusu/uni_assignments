using System;

namespace SquareAndMultiply
{
    class Program
    {
        static void Main(string[] args) 
        {
            const ulong zahl = 5;
            const ulong exponent = 150;
            const ulong modulo = 177;
            ulong currentNumber = zahl;
            var zahlBinary = Convert.ToString((uint) exponent, 2);
            Console.Write("SQM: \\\\" + Environment.NewLine + exponent + " = " + zahlBinary + " \\\\" + Environment.NewLine + "\\textbf{1} \\quad " + zahl + " \\\\" + Environment.NewLine);
            for (var i = 1; i < zahlBinary.Length; i++)
            {
                if (zahlBinary[i].Equals('1'))
                {
                    Console.Write("\\textbf{1} \\quad " + zahl + '*' + currentNumber + "^2\\mod " + modulo + " = ");
                    currentNumber = (zahl * (ulong) Math.Pow(currentNumber, 2)) % modulo;
                    String currentNumberBinary = Convert.ToString((uint) currentNumber, 2);
                    Console.Write(currentNumberBinary + " \\\\" + Environment.NewLine);
                }
                else
                {
                    Console.Write("\\textbf{0} \\quad " + currentNumber + "^2\\mod " + modulo + " = ");
                    currentNumber = (ulong) Math.Pow(currentNumber, 2) % modulo;
                    String currentNumberBinary = Convert.ToString((uint) currentNumber, 2);
                    Console.Write(currentNumberBinary + " \\\\" + Environment.NewLine);
                }
            }
            Console.ReadKey();
        }
    }
}
