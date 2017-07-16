using System;

namespace SquareAndMultiply
{
    class Program
    {
        static void Main(string[] args) 
        {
            const ulong zahl = 23;
            const ulong exponent = 37;
            const ulong modulo = 127;
            ulong currentNumber = zahl;
            var zahlBinary = Convert.ToString((uint) exponent, 2);
            Console.Write("SQM: \\\\" + Environment.NewLine + exponent + " = " + zahlBinary + " \\\\" + Environment.NewLine + "\\textbf{1} \\quad " + zahl + " \\\\" + Environment.NewLine);
            for (var i = 1; i < zahlBinary.Length; i++)
            {
                if (zahlBinary[i].Equals('1'))
                {
                    Console.Write("\\textbf{1} \\quad " + zahl + '*' + currentNumber + "^2\\mod " + modulo + " = ");
                    currentNumber = (zahl * (ulong) Math.Pow(currentNumber, 2)) % modulo;
                    Console.Write(currentNumber + " \\\\" + Environment.NewLine);
                }
                else
                {
                    Console.Write("\\textbf{0} \\quad " + currentNumber + "^2\\mod " + modulo + " = ");
                    currentNumber = (ulong) Math.Pow(currentNumber, 2) % modulo;
                    Console.Write(currentNumber + " \\\\" + Environment.NewLine);
                }
            }
            Console.ReadKey();
        }
    }
}
