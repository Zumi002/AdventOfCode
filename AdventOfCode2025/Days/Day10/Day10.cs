namespace AdventOfCode2025.Days.Day10
{
    public class Day10 : Day
    {
        public Day10() : base(10) {}

        public override void Part1()
        {
            int result = 0;
            foreach (var line in fileReader.Lines)
            {
                Machine machine = new Machine(line);
                var minButtonPresses = machine.MinButtonPresses();
                result += minButtonPresses;
            }
            Console.WriteLine($"For all machines you need {result} button presses.");
        }

        public override void Part2()
        {
            int result = 0;
            int i = 0;
            foreach (var line in fileReader.Lines)
            {
                Machine machine = new Machine(line);
                var minButtonPresses = machine.MinButtonPressesForJoltage();
                result += minButtonPresses;
            }
            Console.WriteLine($"For all joltages you need {result} button presses.");
        }

        public override void Test()
        {
            int result = 0;
            int result2 = 0;
            int i = 0;
            foreach (var line in testFileReader.Lines)
            {
                Machine machine = new Machine(line);
                var minButtonPresses = machine.MinButtonPresses();
                result += minButtonPresses;
                Console.WriteLine($"Machine {i} needed {minButtonPresses} button presses.");
                var minButtonPressesForJoltage = machine.MinButtonPressesForJoltage();
                result2 += minButtonPressesForJoltage;
                Console.WriteLine($"Joltage button presses {minButtonPressesForJoltage}");
            }
            Console.WriteLine($"For all machines you need {result} button presses.");
            Console.WriteLine($"For all joltages you need {result2} button presses.");
        }
    }
}
