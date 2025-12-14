namespace AdventOfCode2025.Days.Day12
{
    public class Day12 : Day
    {
        public Day12() : base(12) { }

        public override void Part1()
        {
            List<Present> presents = new List<Present>();
            var i = 0;
            for (var j = 0; j < 6; j++)
            {
                i++;
                var lines = fileReader.Lines.Skip(i).Take(3).ToList();
                i += 4;
                presents.Add(new Present(lines));
                //presents.Last().Print(Present.Rotation.R90);
            }

            int regionsThatFitPresents = 0;

            for (; i < fileReader.Lines.Count; i++)
            {
                PresentTree presentTree = new PresentTree(fileReader.Lines[i], presents);
                //presentTree.Print();
                var res = presentTree.CanFit();
                //presentTree.Print();
                if (res)
                {
                    regionsThatFitPresents++;
                }
            }

            Console.WriteLine($"Regions that fits presents {regionsThatFitPresents} <- heurisitc solve not sure");
        }

        public override void Part2()
        {
            Console.WriteLine("Click!");
        }

        public override void Test()
        {
            List<Present> presents = new List<Present>();
            var i = 0;
            for (var j = 0; j < 6; j++)
            {
                i++;
                var lines = testFileReader.Lines.Skip(i).Take(3).ToList();
                i += 4;
                presents.Add(new Present(lines));
                //presents.Last().Print(Present.Rotation.R90);
            }

            int regionsThatFitPresents = 0;

            for (; i < testFileReader.Lines.Count; i++)
            {
                PresentTree presentTree = new PresentTree(testFileReader.Lines[i], presents);
                //presentTree.Print();
                var res = presentTree.CanFit();
                //presentTree.Print();
                if(res)
                {
                    regionsThatFitPresents++;
                }
            }

            Console.WriteLine($"Regions that fits presents {regionsThatFitPresents} <- it fails");
        }
    }
}
