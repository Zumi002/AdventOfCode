namespace AdventOfCode2025.Days.Day1
{
    public class Day1 : Day
    {
        Dial part1Dial;
        public Day1() : base(1) { }

        public override void Test()
        {
            Dial dial = new Dial(50);
            foreach(var line in testFileReader.Lines)
            {
                int num = int.Parse(line.Substring(1));
                if (line[0] == 'L')
                {
                    dial.RotateLeft(num);
                }
                else
                {
                    dial.RotateRight(num);
                }

                Console.WriteLine($"{dial.Position} {dial.Clicks}");
            }
        }
        public override void Part1()
        {
            part1Dial = new Dial(50);
            int zeros = 0;
            foreach (var line in fileReader.Lines)
            {
                int num = int.Parse(line.Substring(1));
                if (line[0] == 'L')
                {
                    part1Dial.RotateLeft(num);
                }
                else
                {
                    part1Dial.RotateRight(num);
                }

                zeros += part1Dial.Position == 0 ? 1 : 0;
            }

            Console.WriteLine(zeros);
        }

        public override void Part2()
        {
            Console.WriteLine(part1Dial.Clicks);
        }
    }
}
