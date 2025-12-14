namespace AdventOfCode2025.Days.Day4
{
    public class Grid
    {
        public int[][] directions =
        {
            [-1, -1],
            [ -1, 0],
            [ -1, 1],
            [ 0, -1],
            [ 0, 1],
            [ 1, -1],
            [ 1, 0],
            [ 1, 1],
        };
        public char[,] Values;
        public int N
        { get
            {
                return Values.GetLength(0);
            }
        }
        public int M
        {
            get
            {
                return Values.GetLength(1);
            }
        }
        public Grid(List<string> lines)
        {
            int n = lines.Count;
            int m = lines[0].Length;
            Values = new char[n, m];
            int i = 0;
            foreach (string line in lines)
            {
                for (int j = 0; j < m; j++)
                {
                    Values[i, j] = line[j];
                }
                i++;
            }
        }

        public int Neighbours(int x, int y)
        {
            if (x < 0 || y < 0 || x >= M || y >= N)
            {
                return 0;
            }
            int res = 0;
            foreach (var direction in directions)
            {
                int tmpX = x + direction[0];
                int tmpY = y + direction[1];
                if (tmpX < 0 || tmpY < 0 || tmpX >= M || tmpY >= N)
                {
                    continue;
                }
                if (Values[tmpY, tmpX] == '@')
                {
                    res++;
                }
            }
            return res;
        }

        public List<(int, int)> NeighboursList(int x, int y)
        {
            if (x < 0 || y < 0 || x >= M || y >= N)
            {
                return [];
            }
            List<(int, int)> res = new List<(int, int)> ();
            foreach (var direction in directions)
            {
                int tmpX = x + direction[0];
                int tmpY = y + direction[1];
                if (tmpX < 0 || tmpY < 0 || tmpX >= M || tmpY >= N)
                {
                    continue;
                }
                if (Values[tmpY, tmpX] == '@')
                {
                    res.Add((tmpX, tmpY));
                }
            }
            return res;
        }

        public void Print()
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    Console.WriteLine(Values[i, j]);
                }
            }
        }

        public char this[int x, int y]
        {
            get => Values[y, x];
            set => Values[y, x] = value;
        }

    }
}
