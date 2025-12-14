using AdventOfCode2025.Helpers;

namespace AdventOfCode2025.Days.Day6
{
    public class Day6 : Day
    {
        public Day6() : base(6) { }

        public override void Test()
        {
            Compactor compactor = new Compactor();
            foreach (var line in testFileReader.Lines)
            {
                compactor.ParseLine(line);
            }
            Console.WriteLine($"After operations {compactor.PerformOperations()}");
            Compactor compactorVert = new Compactor();
            compactorVert.ParseLineVertical(testFileReader.Lines.Last());
            for (var i = 0; i < testFileReader.Lines.Count - 1; i++)
            {
                compactorVert.ParseLineVertical(testFileReader.Lines[i]);
            }
            Console.WriteLine($"After operations {compactorVert.PerformOperationsVertical()}");
        }

        public override void Part1()
        {
            Compactor compactor = new Compactor();
            foreach (var line in fileReader.Lines)
            {
                compactor.ParseLine(line);
            }
            Console.WriteLine($"After operations {compactor.PerformOperations()}");
        }

        public override void Part2()
        {
            Compactor compactorVert = new Compactor();
            compactorVert.ParseLineVertical(fileReader.Lines.Last());
            for (var i = 0; i < fileReader.Lines.Count - 1; i++)
            {
                compactorVert.ParseLineVertical(fileReader.Lines[i]);
            }
            Console.WriteLine($"After operations {compactorVert.PerformOperationsVertical()}");
        }
    }
}
