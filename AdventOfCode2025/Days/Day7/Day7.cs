namespace AdventOfCode2025.Days.Day7
{
    public class Day7 : Day
    {
        public Day7() : base(7) { }
        public override void Test()
        {
            var tachyonManifold = new TachyonManifold(testFileReader.Lines);
            tachyonManifold.Run();
            Console.WriteLine($"Splits {tachyonManifold.Splits}");
            Console.WriteLine($"Many world {tachyonManifold.RunManyWorld()}");
        }

        public override void Part1()
        {
            var tachyonManifold = new TachyonManifold(fileReader.Lines);
            tachyonManifold.Run();
            Console.WriteLine($"Splits {tachyonManifold.Splits}");
        }

        public override void Part2()
        {
            var tachyonManifold = new TachyonManifold(fileReader.Lines);
            Console.WriteLine($"Many world {tachyonManifold.RunManyWorld()}");
        }
    }
}
