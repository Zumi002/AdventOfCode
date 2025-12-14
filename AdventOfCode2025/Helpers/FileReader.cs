namespace AdventOfCode2025.Helpers
{
    public class FileReader
    {
        public int NoL = 0;
        public List<string> Lines = new List<string>();

        public FileReader(string filePath)
        {
            Lines = ReadLines(filePath).ToList();
            NoL = Lines.Count;
        }
        public static string[] ReadLines(string filePath)
        {
            return System.IO.File.ReadAllLines(filePath);
        }
    }
}
