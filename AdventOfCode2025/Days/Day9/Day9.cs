namespace AdventOfCode2025.Days.Day9
{
    public class Day9 : Day
    {
        public Day9() : base(9) { }

        public override void Part1()
        {
            List<(long x, long y)> redTiles = new List<(long, long)>();
            foreach (var line in fileReader.Lines)
            {
                var tile = line.Split(',').Select(long.Parse).ToArray();
                redTiles.Add((tile[0], tile[1]));
            }
            long biggestArea = 0;
            foreach (var tile1 in redTiles)
            {
                foreach (var tile2 in redTiles)
                {
                    long area = (Math.Abs(tile1.x - tile2.x) + 1) * (Math.Abs(tile1.y - tile2.y) + 1);
                    biggestArea = Math.Max(biggestArea, area);
                }
            }
            Console.WriteLine($"Biggest area: {biggestArea}");
        }

        public override void Part2()
        {
            List<(long x, long y)> redTiles = new List<(long, long)>();
            foreach (var line in fileReader.Lines)
            {
                var tile = line.Split(',').Select(long.Parse).ToArray();
                redTiles.Add((tile[0], tile[1]));
            }
            TiledFloor tiledFloor = new TiledFloor(redTiles);
            Console.WriteLine($"Biggest constrained area: {tiledFloor.BiggestConstrainedRectangleArea()}");
        }

        public override void Test()
        {
            List<(long x, long y)> redTiles = new List<(long, long)>();
            foreach (var line in testFileReader.Lines)
            {
                var tile = line.Split(',').Select(long.Parse).ToArray();
                redTiles.Add((tile[0], tile[1]));
            }
            long biggestArea = 0;
            foreach (var tile1 in redTiles)
            {
                foreach (var tile2 in redTiles)
                {
                    long area = (Math.Abs(tile1.x-tile2.x)+1)*(Math.Abs(tile1.y-tile2.y)+1);
                    biggestArea = Math.Max(biggestArea, area);
                }
            }
            Console.WriteLine($"Biggest area: {biggestArea}");
            TiledFloor tiledFloor = new TiledFloor(redTiles);
            Console.WriteLine($"Biggest constrained area: {tiledFloor.BiggestConstrainedRectangleArea()}");
        }
    }
}
