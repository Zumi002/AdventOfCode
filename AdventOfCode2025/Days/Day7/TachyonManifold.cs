using System.Drawing;

namespace AdventOfCode2025.Days.Day7
{
    public class TachyonManifold
    {
        char[,] diagram;
        Point start;
        public int Splits { get; private set; }
        public TachyonManifold(List<string> lines)
        {
            int n = lines.Count;
            int m = lines[0].Length;
            diagram = new char[m, n];
            for (var i = 0; i < n; i++)
            {
                for (var j = 0; j < m; j++)
                {
                    diagram[j, i] = lines[i][j];
                    if (lines[i][j] == 'S')
                    {
                        start = new Point(j, i);
                    }
                }
            }
            Splits = 0;
        }

        public void Run()
        {
            Queue<Point> nextPoints = new Queue<Point>();
            bool[,] visited = new bool[diagram.GetLength(0), diagram.GetLength(1)];
            nextPoints.Enqueue(start);
            while (nextPoints.Count > 0)
            {
                Point point = nextPoints.Dequeue();
                if (point.X < 0 || point.X >= diagram.GetLength(0) || point.Y < 0 || point.Y >= diagram.GetLength(1))
                {
                    continue;
                }
                if (visited[point.X, point.Y])
                {
                    continue;
                }
                visited[point.X, point.Y] = true;
                if (diagram[point.X, point.Y] == '^')
                {
                    nextPoints.Enqueue(new Point(point.X + 1, point.Y));
                    nextPoints.Enqueue(new Point(point.X - 1, point.Y));
                    Splits++;
                }
                else
                {
                    nextPoints.Enqueue(new Point(point.X, point.Y + 1));
                }
            }
        }
        public long RunManyWorld()
        {
            Queue<Point> nextPoints = new Queue<Point>();
            bool[,] visited = new bool[diagram.GetLength(0), diagram.GetLength(1)];
            long[,] times = new long[diagram.GetLength(0), diagram.GetLength(1)];
            times[start.X, start.Y] = 1;
            nextPoints.Enqueue(start);
            while (nextPoints.Count > 0)
            {
                int pointsToCheck = nextPoints.Count;
                for (var i = 0; i < pointsToCheck; i++)
                {
                    Point point = nextPoints.Dequeue();
                    if (point.X < 0 || point.X >= diagram.GetLength(0) || point.Y < 0 || point.Y >= diagram.GetLength(1))
                    {
                        continue;
                    }

                    if (visited[point.X, point.Y])
                    {
                        continue;
                    }
                    visited[point.X, point.Y] = true;
                    if(point.Y >= diagram.GetLength(1) - 1)
                    {
                        continue;
                    }
                    if (diagram[point.X, point.Y] == '^')
                    {
                        nextPoints.Enqueue(new Point(point.X + 1, point.Y + 1));
                        times[point.X + 1, point.Y + 1] += times[point.X, point.Y];
                        nextPoints.Enqueue(new Point(point.X - 1, point.Y + 1));
                        times[point.X - 1, point.Y + 1] += times[point.X, point.Y];
                    }
                    else
                    {
                        nextPoints.Enqueue(new Point(point.X, point.Y + 1));
                        times[point.X, point.Y + 1] += times[point.X, point.Y];
                    }
                }
            }

            long result = 0;
            for(var j = 0; j < times.GetLength(0); j++)
            {
                result += times[j, times.GetLength(1) - 1];
            }
            return result;
        }
    }
}
