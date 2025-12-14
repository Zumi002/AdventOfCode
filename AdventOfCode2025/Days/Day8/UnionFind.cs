namespace AdventOfCode2025.Days.Day8
{
    public class UnionFind
    {
        public int[] parent { get; private set; }
        public int[] size { get; private set; }
        public UnionFind(int numberOfSets) 
        {
            parent = Enumerable.Range(0, numberOfSets).ToArray();
            size = Enumerable.Repeat(1, numberOfSets).ToArray();
        }

        public int Find(int x)
        {
            if (parent[x] != x)
            {
                parent[x] = Find(parent[x]);
                return parent[x];
            }

            return x;
        }

        public void Union(int x, int y)
        {
            int s1 = Find(x);
            int s2 = Find(y);

            if (s1 == s2)
            {
                return;
            }

            if (size[s1] < size[s2])
            {
                (s1, s2) = (s2, s1);
            }

            parent[s2] = s1;
            size[s1] += size[s2];
        }
    }
}
