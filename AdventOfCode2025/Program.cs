using AdventOfCode2025.Days;
using AdventOfCode2025.Days.Day1;
using AdventOfCode2025.Days.Day2;
using AdventOfCode2025.Days.Day3;
using AdventOfCode2025.Days.Day4;
using AdventOfCode2025.Days.Day5;
using AdventOfCode2025.Days.Day6;
using AdventOfCode2025.Days.Day7;
using AdventOfCode2025.Days.Day8;
using AdventOfCode2025.Days.Day9;
using AdventOfCode2025.Days.Day10;
using AdventOfCode2025.Days.Day11;
using AdventOfCode2025.Days.Day12;

namespace AdventOfCode2025
{
    internal class Program
    {
        static readonly List<Day> days = new()
        {
            new Day1(),
            new Day2(),
            new Day3(),
            new Day4(),
            new Day5(),
            new Day6(),
            new Day7(),
            new Day8(),
            new Day9(),
            new Day10(),
            new Day11(),
            new Day12()
        };
        static void Main(string[] args)
        {
            foreach (Day day in days)
            {
                day.Solve();
            }
            //Day today = days.Last();
            //today.Test();
            //today.Solve();
        }
    }
}
