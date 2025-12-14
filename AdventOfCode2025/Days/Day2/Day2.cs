using AdventOfCode2025.Helpers;

namespace AdventOfCode2025.Days.Day2
{
    public class Day2 : Day
    {
        public Day2() : base(2) { }
        public override void Test()
        {
            long result = 0;
            long result2 = 0;
            var ranges = testFileReader.Lines[0].Split(',');
            foreach (var range in ranges)
            {
                var ends = range.Split("-");
                long begin = long.Parse(ends[0]);
                long end = long.Parse(ends[1]);
                var longs = RepeatsKTimesOnRange(begin, end, 2);
                foreach (var found in longs)
                {
                    Console.WriteLine($"Found in {begin}-{end}: {found}");
                    result += found;
                } 
                var rangeResult = RepeatsOnRangeSum(begin, end);
                result2 += rangeResult;
            }
            Console.WriteLine($"Pass: {result} \nPass2: {result2}");
        }

        public override void Part1()
        {
            long result = 0;
            var ranges = fileReader.Lines[0].Split(',');
            foreach (var range in ranges)
            {
                var ends = range.Split("-");
                long begin = long.Parse(ends[0]);
                long end = long.Parse(ends[1]);
                var longs = RepeatsKTimesOnRange(begin, end, 2);
                foreach (var found in longs)
                {
                    result += found;
                }
            }
            Console.WriteLine(result);
        }

        public override void Part2()
        {
            long result = 0;
            var ranges = fileReader.Lines[0].Split(',');
            foreach (var range in ranges)
            {
                var ends = range.Split("-");
                long begin = long.Parse(ends[0]);
                long end = long.Parse(ends[1]);
                var rangeResult = RepeatsOnRangeSum(begin, end);
                result += rangeResult;
            }
            Console.WriteLine(result);
        }

        public long[] RepeatsKTimesOnRange(long a, long b, long kTimesRepeat)
        {
            List<long> digits = new List<long>();
            long tens = 0;
            long tmp = a;
            while(tmp > 0)
            {
                tmp /= 10;
                tens++;
            }
            tens = (tens+kTimesRepeat-1)/ kTimesRepeat;
            for (var i = 0; i < tens-1; i++)
            {
                digits.Add(0);
            }
            digits.Add(1);
            long now = Getlong(digits, kTimesRepeat);
            List<long> res = new List<long>();
            while(now <= b)
            {
                if (now >= a)
                {
                    res.Add(now);
                }
                NextDigits(digits);
                now = Getlong(digits, kTimesRepeat);
            }
            return res.ToArray();
        }
        public long RepeatsOnRangeSum(long a, long b)
        {
            long tens = 0;
            long tmp = b;
            long result = 0;
            while (tmp > 0)
            {
                tmp /= 10;
                tens++;
            }
            HashSet<long> seen = new HashSet<long>();
            for (var i = 2; i <= tens; i++)
            {
                foreach (var found in RepeatsKTimesOnRange(a, b, i))
                {
                    if(seen.Contains(found))
                    {
                        continue;
                    }
                    result += found;
                    seen.Add(found);
                    //Console.WriteLine($"Found in {a}-{b}: {found}");
                }
            }
            return result;
        }
        public void NextDigits(List<long> digits)
        {
            bool braked = false;
            for (var i = 0; i < digits.Count; i++)
            {
                if (digits[i] == 9)
                {
                    digits[i] = 0;
                    continue;
                }
                digits[i] = digits[i] + 1;
                braked = true;
                break;
            }
            if (!braked)
            {
                digits.Add(1);
            }
        }
        public long Getlong(List<long> digits, long kTimesRepeat)
        {
            long multi = 1;
            long res = 0;
            long once = 0;
            foreach (long i in digits)
            {
                res += i * multi;
                multi *= 10;
            }
            once = res;
            for (var i = 1; i<kTimesRepeat; i++)
            {
                res *= multi;
                res += once;
            }
            return res;
        }
    }
}
