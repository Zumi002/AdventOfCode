namespace AdventOfCode2025.Days.Day5
{
    public struct Range : IComparable
    {
        public long Start;
        public long End;

        public Range(long s, long e) 
        {
            Start = s;
            End = e;
        }

        public bool CanMerge(Range r)
        {
            if (r.Start > End+1 || r.End + 1 < Start)
            {
                return false;
            }
            return true;
        }

        public Range Merge(Range r)
        {
            return new Range(Math.Min(r.Start, Start), Math.Max(r.End, End));
        }

        public int CompareTo(Range r)
        {
            return Start.CompareTo(r.Start);
        }

        public bool Contains(long s)
        {
            return s >= Start && s <= End;
        }

        public int CompareTo(object? obj)
        {
            return Start.CompareTo(((Range)obj).Start);
        }
    }
}
