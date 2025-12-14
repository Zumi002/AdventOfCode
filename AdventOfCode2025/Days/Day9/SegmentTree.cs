
namespace AdventOfCode2025.Days.Day9
{
    public struct Interval
    {
        public int start;
        public int end;
        public Interval(int start, int end)
        {
            this.start = start;
            this.end = end;
        }
        public int m => (start + end) / 2;
    }

    public class SegmentTree<T>
    {
        public Interval interval;
        public T Value;
        public SegmentTree<T>? left, right;
        public Func<T, T, T> FoldingRule;
        public SegmentTree(List<T> values, int l, int r, Func<T, T, T> foldingRule)
        {
            FoldingRule = foldingRule;
            interval = new Interval(l, r);
            if (l == r)
            {
                Value = values[l];
                left = null;
                right = null;
                return;
            }

            int m = (l + r) / 2;
            left = new SegmentTree<T>(values, l, m , foldingRule);
            right = new SegmentTree<T>(values, m + 1, r, foldingRule);
            Value = foldingRule(left.Value, right.Value);
        }
        public SegmentTree(List<T> values, Func<T, T, T> foldingRule) : this(values, 0, values.Count - 1, foldingRule){ }

        public T GetInterval(int l, int r)
        {
            if(interval.start == l && interval.end == r)
            {
                return Value;
            }

            if(left == null && right == null)
            {
                throw new Exception("Unexpected subintervals");
            }
            T? returnValue = default;
            bool getFromLeft = false;
            if(l <= interval.m)
            {
                returnValue = left!.GetInterval(l, Math.Min(interval.m, r));
                getFromLeft = true;
            }
            if (r > interval.m)
            {
                T rightValue = right!.GetInterval(Math.Max(interval.m + 1, l), r);
                if (getFromLeft)
                {
                    returnValue = FoldingRule(returnValue!, rightValue);
                }
                else
                {
                    returnValue = rightValue;
                }
            }

            return returnValue!;
        }
    }
}
