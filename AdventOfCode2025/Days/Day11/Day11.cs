namespace AdventOfCode2025.Days.Day11
{
    public class Day11 : Day
    {
        public Day11() : base(11) { }

        public override void Part1()
        {
            Graph g = new Graph(fileReader.Lines);
            Console.WriteLine($"Paths from you to out: {g.PathsFromYouToOut()}");
        }

        public override void Part2()
        {
            Graph g = new Graph(fileReader.Lines);
            long fromSvrToFFT = g.PathsFromNodeToNode("svr", "fft");
            long fromFFTToDAC = g.PathsFromNodeToNode("fft", "dac");
            long fromDACToOut = g.PathsFromNodeToNode("dac", "out");
            long res = fromSvrToFFT*fromFFTToDAC*fromDACToOut;
            long fromSvrToDAC = g.PathsFromNodeToNode("svr", "dac");
            long fromDACToFFT = g.PathsFromNodeToNode("dac", "fft");
            long fromFFTToOut = g.PathsFromNodeToNode("fft", "out");
            res += fromSvrToDAC * fromDACToFFT * fromFFTToOut;
            Console.WriteLine($"Paths from svr to out, going through dac and fft {res}");
        }

        public override void Test()
        {
            Graph g = new Graph(testFileReader.Lines);
            //Console.WriteLine($"Paths from you to out: {g.PathsFromYouToOut()}");
            int fromSvrToFFT = g.PathsFromNodeToNode("svr", "fft");
            int fromFFTToDAC = g.PathsFromNodeToNode("fft", "dac");
            int fromDACToOut = g.PathsFromNodeToNode("dac", "out");
            int res = fromSvrToFFT * fromFFTToDAC * fromDACToOut;
            int fromSvrToDAC = g.PathsFromNodeToNode("svr", "dac");
            int fromDACToFFT = g.PathsFromNodeToNode("dac", "fft");
            int fromFFTToOut = g.PathsFromNodeToNode("fft", "out");
            res += fromSvrToDAC * fromDACToFFT * fromFFTToOut;
            Console.WriteLine($"Paths from svr to out, going through dac and fft {res}");
        }
    }
}
