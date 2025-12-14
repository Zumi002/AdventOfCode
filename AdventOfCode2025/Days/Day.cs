using AdventOfCode2025.Helpers;
using System.Diagnostics;

namespace AdventOfCode2025.Days
{
    public abstract class Day
    {
        protected int dayNumber;
        protected FileReader fileReader;
        protected FileReader testFileReader;
        protected Day(int dayNumber) 
        {
            fileReader = new FileReader($"Inputs/Day{dayNumber}/input.txt");
            testFileReader = new FileReader($"Inputs/Day{dayNumber}/test.txt");
            this.dayNumber = dayNumber;
        }

        public void Solve()
        {

            Console.WriteLine($"Day {dayNumber} - Part 1: ");
            Stopwatch sw = Stopwatch.StartNew();
            Part1();
            sw.Stop();
            Console.WriteLine($"Time: {sw.ElapsedMilliseconds}ms");
            Console.WriteLine($"Day {dayNumber} - Part 2: ");
            sw.Restart();
            Part2();
            sw.Stop();
            Console.WriteLine($"Time: {sw.ElapsedMilliseconds}ms");
            Console.WriteLine("");
        }
        public abstract void Test();
        public abstract void Part1();
        public abstract void Part2();
    }
}
