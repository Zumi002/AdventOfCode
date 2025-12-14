namespace AdventOfCode2025.Days.Day11
{
    public class Node
    {
        public string Name;
        public List<Node> Connection;
        public int ConsToOut;

        public Node(string name)
        {
            Name = name;
            Connection = new List<Node>();
        }

        public void AddConnection(Node connection)
        {
            Connection.Add(connection);
        }
    }
}
