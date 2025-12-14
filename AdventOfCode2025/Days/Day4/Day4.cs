using AdventOfCode2025.Helpers;

namespace AdventOfCode2025.Days.Day4
{
    public class Day4 : Day
    {
        public Day4() : base(4) { }

        public override void Test()
        {
            Grid grid = new Grid(testFileReader.Lines);
            int result = 0;
            for (int i = 0; i < grid.M; i++)
            {
                for (int j = 0; j < grid.N; j++)
                {
                    if (grid[i, j] != '@')
                    {
                        continue;
                    }
                    result += grid.Neighbours(i, j) < 4 ? 1 : 0;
                    Console.WriteLine($"{i} {j} {result}");
                }
            }
            Console.WriteLine($"Rolls: {result}");
        }

        public override void Part1()
        {
            Grid grid = new Grid(fileReader.Lines);
            int result = 0;
            for (int i = 0; i < grid.M; i++)
            {
                for (int j = 0; j < grid.N; j++)
                {
                    if (grid[i, j] != '@')
                    {
                        continue;
                    }
                    result += grid.Neighbours(i, j) < 4 ? 1 : 0;
                }
            }
            Console.WriteLine($"Rolls: {result}");
        }

        public override void Part2()
        {
            Grid grid = new Grid(fileReader.Lines);
            int result = 0;
            HashSet<(int, int)> positionsToCheckNext = new HashSet<(int, int)>();

            for (int i = 0; i < grid.M; i++)
            {
                for (int j = 0; j < grid.N; j++)
                {
                    if (grid[i, j] != '@')
                    {
                        continue;
                    }
                    var list = grid.NeighboursList(i, j);
                    if(list.Count < 4)
                    {
                        result++;
                        grid[i, j] = '.';
                        positionsToCheckNext.Remove((i, j));
                        foreach (var item in list)
                        {
                            positionsToCheckNext.Add(item);
                        }
                    }
                }
            }

            while(positionsToCheckNext.Count > 0)
            {
                var positions = positionsToCheckNext.ToArray();
                positionsToCheckNext.Clear();
                foreach ((var x, var y) in positions)
                {
                    if (grid[x, y] != '@')
                    {
                        continue;
                    }
                    var list = grid.NeighboursList(x, y);
                    if (list.Count < 4)
                    {
                        result++;
                        grid[x, y] = '.';
                        positionsToCheckNext.Remove((x, y));
                        foreach (var item in list)
                        {
                            positionsToCheckNext.Add(item);
                        }
                    }
                }
            }

            Console.WriteLine($"Rolls: {result}");
        }
    }
}
