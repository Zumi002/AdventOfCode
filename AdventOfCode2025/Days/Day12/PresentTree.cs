namespace AdventOfCode2025.Days.Day12
{
    public class PresentTree
    {
        public Row[] rows;
        public List<Present> presents;
        public List<int> presentsToFit;

        public int X;
        public int Y;


        public PresentTree(string schema, List<Present> presents)
        {
            var parts = schema.Split(':');
            var sizes = parts[0].Split('x').Select(int.Parse).ToList();
            CreateRows(sizes[0], sizes[1]);
            this.presents = presents;
            presentsToFit = parts[1].Trim().Split(' ').Select(int.Parse).ToList();
        }

        public bool CanFit()
        {
            for (var i = 0; i < Y - 2; i++)
            {
                for (var j = 0; j < X - 2; j++)
                {

                    for (var k = 0; k < presents.Count; k++)
                    {
                        if (presentsToFit[k] > 0)
                        {
                            var result = presents[k].TryFit(rows[i], rows[i + 1], rows[i + 2], j);
                            if (result.fitted)
                            {
                                rows[i] = result.r1;
                                rows[i + 1] = result.r2;
                                rows[i + 2] = result.r3;
                                presentsToFit[k]--;
                                break;
                            }
                        }
                    }

                }
            }

            foreach (var toFit in presentsToFit)
            {
                if (toFit > 0)
                {
                    return false;

                }
            }
            return true;
        }

        public void Print()
        {
            Console.WriteLine();
            for (var i = 0; i < Y; i++)
            {
                for (var j = 0; j < X; j++)
                {
                    Console.Write(rows[i].GetChar(j));
                }
                Console.WriteLine();
            }
        }
        private void CreateRows(int x, int y)
        {
            rows = new Row[y];
            Row mask = Row.Full();
            mask = mask >> (64 - x);
            for (var i = 0; i < y; i++)
            {
                rows[i] = new Row();
                rows[i] = rows[i].Subtract(mask);
            }
            X = x;
            Y = y;
        }
    }
}
