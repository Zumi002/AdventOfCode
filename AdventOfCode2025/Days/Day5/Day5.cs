using AdventOfCode2025.Helpers;

namespace AdventOfCode2025.Days.Day5
{
    public class Day5 : Day
    {
        public Day5() : base(5) {}
        public override void Test()
        {
            List<Range> ranges = new List<Range>();
            int i = 0;
            while (testFileReader.Lines[i].Length > 0)
            {
                var line = testFileReader.Lines[i];
                var ends = line.Split('-');
                var start = long.Parse(ends[0]);
                var end = long.Parse(ends[1]);
                ranges.Add(new Range(start, end));
                i++;
            }
            i++;
            ranges.Sort();
            var nowRange = ranges[0];
            var mergedRanges = new List<Range>();
            for (var j = 1; j < ranges.Count; j++)
            {
                if (ranges[j].CanMerge(nowRange))
                {
                    nowRange = ranges[j].Merge(nowRange);
                }
                else
                {
                    mergedRanges.Add(nowRange);
                    nowRange = ranges[j];
                }
            }
            mergedRanges.Add(nowRange);

            int res = 0;
            for (; i < testFileReader.Lines.Count; i++)
            {
                long value = long.Parse(testFileReader.Lines[i]);
                if(isInRanges(mergedRanges, value))
                {
                    res++;
                    Console.WriteLine($"{value} is in ranges");
                }
            }

            Console.WriteLine($"Fresh ingridients: {res}");
            long res2 = 0;
            foreach (var range in mergedRanges)
            {
                res2 += range.End - range.Start + 1;
            }
            Console.WriteLine($"All fresh IDs: {res2}");
        }

        public override void Part1()
        {
            List<Range> ranges = new List<Range>();
            int i = 0;
            while (fileReader.Lines[i].Length > 0)
            {
                var line = fileReader.Lines[i];
                var ends = line.Split('-');
                var start = long.Parse(ends[0]);
                var end = long.Parse(ends[1]);
                ranges.Add(new Range(start, end));
                i++;
            }
            i++;
            ranges.Sort();
            var nowRange = ranges[0];
            var mergedRanges = new List<Range>();
            for (var j = 1; j < ranges.Count; j++)
            {
                if (ranges[j].CanMerge(nowRange))
                {
                    nowRange = ranges[j].Merge(nowRange);
                }
                else
                {
                    mergedRanges.Add(nowRange);
                    nowRange = ranges[j];
                }
            }
            mergedRanges.Add(nowRange);

            int res = 0;
            for (; i < fileReader.Lines.Count; i++)
            {
                long value = long.Parse(fileReader.Lines[i]);
                if (isInRanges(mergedRanges, value))
                {
                    res++;
                }
            }

            Console.WriteLine($"Fresh ingridients: {res}");
        }

        public override void Part2()
        {
            List<Range> ranges = new List<Range>();
            int i = 0;
            while (fileReader.Lines[i].Length > 0)
            {
                var line = fileReader.Lines[i];
                var ends = line.Split('-');
                var start = long.Parse(ends[0]);
                var end = long.Parse(ends[1]);
                ranges.Add(new Range(start, end));
                i++;
            }
            i++;
            ranges.Sort();
            var nowRange = ranges[0];
            var mergedRanges = new List<Range>();
            for (var j = 1; j < ranges.Count; j++)
            {
                if (ranges[j].CanMerge(nowRange))
                {
                    nowRange = ranges[j].Merge(nowRange);
                }
                else
                {
                    mergedRanges.Add(nowRange);
                    nowRange = ranges[j];
                }
            }
            mergedRanges.Add(nowRange);

            long res = 0;
            foreach (var range in mergedRanges)
            {
                res += range.End - range.Start + 1;
            }
            Console.WriteLine($"All fresh IDs: {res}");
        }

        public bool isInRanges(List<Range> sortedRanges, long value)
        {
            int l = 0;
            int r = sortedRanges.Count;
            int m = 0;
            while (l < r)
            {
                m = (r + l)  / 2;
                if (sortedRanges[m].Start > value)
                {
                    r = m;
                }
                else if (sortedRanges[m].End < value)
                {
                    l = m + 1;
                }
                else
                {
                    break;
                }
            }

            return sortedRanges[m].Contains(value);
        }
    }
}
