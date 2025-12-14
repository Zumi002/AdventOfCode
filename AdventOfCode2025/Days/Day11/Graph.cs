namespace AdventOfCode2025.Days.Day11
{
    public class Graph
    {
        public Dictionary<string, Node> Nodes;
        public Graph(List<string> nodeDescripitons) 
        {
            Nodes = new Dictionary<string, Node>();
            foreach (var nodeDesc in nodeDescripitons)
            {
                string name = nodeDesc.Split(':').First();
                Nodes.Add(name, new Node(name));
            }
            Nodes.Add("out", new Node("out"));
            foreach (var nodeDesc in nodeDescripitons)
            {
                string[] descriptions = nodeDesc.Split(':');
                string name = descriptions[0];
                string connectionsDesc = descriptions[1].Trim();
                string[] connections = connectionsDesc.Split(" ");
                foreach (var connection in connections)
                {
                    Nodes[name].AddConnection(Nodes[connection]);
                }
            }
        }
        public int PathsFromNodeToNode(string from, string to)
        {
            Stack<Node> nodesToVisit = new Stack<Node>();
            Dictionary<string, int> states = new Dictionary<string, int>();
            nodesToVisit.Push(Nodes[from]);
            Nodes[to].ConsToOut = 1;
            foreach (var pair in Nodes)
            {
                states[pair.Key] = 0;
            }
            states[to] = 2;
            while (nodesToVisit.Count > 0)
            {
                var node = nodesToVisit.Pop();
                if (states[node.Name] == 2)
                {
                    continue;
                }
                if (states[node.Name] == 1)
                {
                    int res = 0;
                    foreach (var connection in node.Connection)
                    {
                        res += connection.ConsToOut;
                    }
                    node.ConsToOut = res;
                    states[node.Name] = 2;
                    continue;
                }

                nodesToVisit.Push(node);
                foreach (var connection in node.Connection)
                {
                    if (states[connection.Name] == 1)
                    {
                        continue;
                    }
                    if (states[connection.Name] == 2)
                    {
                        continue;
                    }
                    nodesToVisit.Push(connection);
                }

                states[node.Name] = 1;
            }

            return Nodes[from].ConsToOut;
        }

        public int PathsFromYouToOut()
        {
            return PathsFromNodeToNode("you", "out");
        }
    }
}
