namespace AdventOfCode2025.Days.Day8
{
    public class Day8 : Day
    {
        public Day8() : base(8) { }
        public override void Part1()
        {
            List<int[]> junctions = new List<int[]>();
            foreach (var line in fileReader.Lines)
            {
                int[] junction = line.Split(',').Select(int.Parse).ToArray();
                junctions.Add(junction);
            }

            List<(float dist, int j1, int j2)> pairs = new List<(float, int, int)>();

            for (var i = 0; i < junctions.Count; i++)
            {
                for (var j = i + 1; j < junctions.Count; j++)
                {
                    pairs.Add((DistanceSQ(junctions[i], junctions[j]), i, j));
                }
            }

            pairs.Sort();

            UnionFind uf = new UnionFind(junctions.Count);
            for (int i = 0; i < 1000; i++)
            {
                uf.Union(pairs[i].j1, pairs[i].j2);
            }

            List<int> circutsSizes = new List<int>();
            for (int i = 0; i < junctions.Count; i++)
            {
                if (uf.parent[i] == i)
                {
                    circutsSizes.Add(uf.size[i]);
                }
            }

            circutsSizes.Sort();
            var top3Sizes = circutsSizes.TakeLast(3);
            long result = 1;
            foreach (var size in top3Sizes)
            {
                result *= size;
            }
            Console.WriteLine($"Three biggest circuts multiplied {result}");
        }

        public override void Part2()
        {
            List<int[]> junctions = new List<int[]>();
            foreach (var line in fileReader.Lines)
            {
                int[] junction = line.Split(',').Select(int.Parse).ToArray();
                junctions.Add(junction);
            }

            List<(float dist, int j1, int j2)> pairs = new List<(float, int, int)>();

            for (var i = 0; i < junctions.Count; i++)
            {
                for (var j = i + 1; j < junctions.Count; j++)
                {
                    pairs.Add((DistanceSQ(junctions[i], junctions[j]), i, j));
                }
            }

            pairs.Sort();

            UnionFind uf = new UnionFind(junctions.Count);
            (int j1, int j2) lastPair = (pairs[0].j1, pairs[0].j2);
            for (int i = 0; i < pairs.Count; i++)
            {
                uf.Union(pairs[i].j1, pairs[i].j2);
                if (uf.size[uf.Find(pairs[i].j1)] == junctions.Count)
                {
                    lastPair = (pairs[i].j1, pairs[i].j2);
                    break;
                }
            }

            long result = junctions[lastPair.j1][0] * junctions[lastPair.j2][0];
            Console.WriteLine($"Last pair to connect X*X  {result}");
        }

        public override void Test()
        {
            List<int[]> junctions = new List<int[]>();
            foreach (var line in testFileReader.Lines)
            {
                int[] junction = line.Split(',').Select(int.Parse).ToArray();
                junctions.Add(junction);
            }

            List<(float dist, int j1, int j2)> pairs = new List<(float, int, int)> ();

            for (var i = 0; i < junctions.Count; i++)
            {
                for(var j = i + 1; j < junctions.Count; j++)
                {
                    pairs.Add((DistanceSQ(junctions[i], junctions[j]), i, j));
                }
            }

            pairs.Sort();

            UnionFind uf = new UnionFind(junctions.Count);
            for(int i = 0; i < 10; i++)
            {
                uf.Union(pairs[i].j1, pairs[i].j2);
            }
            
            List<int> circutsSizes = new List<int>();
            for(int i = 0; i < junctions.Count; i++)
            {
                if (uf.parent[i] == i)
                {
                    circutsSizes.Add(uf.size[i]);
                }
            }

            circutsSizes.Sort();
            var top3Sizes = circutsSizes.TakeLast(3);
            long result = 1;
            Console.Write("Biggest circuts: ");
            foreach (var size in top3Sizes)
            {
                Console.Write($"{size} ");
                result *= size;
            }
            Console.WriteLine($"\nThree biggest circuts multiplied {result}");

            (int j1, int j2) lastPair = (pairs[0].j1, pairs[0].j2);
            for (int i = 10; i < pairs.Count; i++)
            {
                uf.Union(pairs[i].j1, pairs[i].j2);
                if (uf.size[uf.Find(pairs[i].j1)] == junctions.Count)
                {
                    lastPair = (pairs[i].j1, pairs[i].j2);
                    break;
                }
            }

            long result2 = junctions[lastPair.j1][0] * junctions[lastPair.j2][0];
            Console.WriteLine($"Last pair to connect X*X {result2}");
        }

        private float DistanceSQ(int[] j1, int[] j2)
        {
            return (float)((long)j1[0] - j2[0]) * ((long)j1[0] - j2[0]) +
                (float)((long)j1[1] - j2[1]) * ((long)j1[1] - j2[1]) +
                (float)((long)j1[2] - j2[2]) * ((long)j1[2] - j2[2]);
        }
    }
}
