using System.Data.Common;

namespace AdventOfCode2025.Days.Day6
{
    public class Compactor
    {
        public enum MathOperation
        {
            Add,
            Multiply
        }
        List<List<long>> Layers;
        List<MathOperation> Operations;
        List<int> OperationSize;

        public Compactor()
        {
            Layers = new List<List<long>>();
            Operations = new List<MathOperation>();
            OperationSize = new List<int>();
        }

        public void ParseLine(string line)
        {
            var columns = line.Split(' ').Where(c => c.Length > 0).ToList();
            if (columns.Any() && (columns[0] == "+" || columns[0] == "*"))
            {
                AddOperations(columns);
            }
            else
            {
                Layers.Add(columns.Select(c => long.Parse(c)).ToList());
            }
        }

        public void ParseLineVertical(string line)
        {
            if (line[0] == '+' || line[0] == '*')
            {
                AddVerticalOperations(line);
            }
            if (Operations.Count <= 0)
            {
                return;
            }

            int i = 0;
            int op = 0;
            foreach (var operationSize in OperationSize)
            {
                for (int j = 0; j < operationSize; j++)
                {
                    if (char.IsDigit(line[i]))
                    {
                        Layers[op][j] *= 10;
                        Layers[op][j] += long.Parse("" + line[i]);
                    }
                    i++;
                }
                i++;
                op++;
            }
        }

        private void AddOperations(List<string> columns)
        {
            foreach (var column in columns)
            {
                if (column == "+")
                {
                    Operations.Add(MathOperation.Add);
                }
                else
                {
                    Operations.Add(MathOperation.Multiply);
                }
            }
        }

        private void AddVerticalOperations(string line)
        {
            int startIndex = -1;
            bool added = false;
            for (int i = 0; i < line.Length; i++)
            {
                added = false;
                if (line[i] == '+')
                {
                    Operations.Add(MathOperation.Add);
                    added = true;
                }
                else if (line[i] == '*')
                {
                    Operations.Add(MathOperation.Multiply);
                    added = true;
                }

                if(added)
                {
                    if (startIndex != -1)
                    {
                        OperationSize.Add(i - startIndex - 1);
                        Layers.Add(Enumerable.Repeat((long)0, i - startIndex - 1).ToList());
                    }
                    startIndex = i;
                }
            }
            OperationSize.Add(line.Length - startIndex);
            Layers.Add(Enumerable.Repeat((long)0, line.Length - startIndex).ToList());
        }

        public long PerformOperations()
        {
            List<long> results = Layers.First();
            for (int i = 1; i < Layers.Count; i++)
            {
                for (int j = 0; j < results.Count; j++)
                {
                    if (Operations[j] == MathOperation.Add)
                    {
                        results[j] += Layers[i][j];
                    }
                    else
                    {
                        results[j] *= Layers[i][j];
                    }
                }
            }

            return results.Aggregate((prev, current) => prev + current);
        }

        public long PerformOperationsVertical()
        {
            List<long> results = Layers.Select(l => l.First()).ToList();
            for (int i = 0; i < Operations.Count; i++)
            {
                for (int j = 1; j < Layers[i].Count; j++)
                {
                    if (Operations[i] == MathOperation.Add)
                    {
                        results[i] += Layers[i][j];
                    }
                    else
                    {
                        results[i] *= Layers[i][j];
                    }
                }
            }

            return results.Aggregate((prev, current) => prev + current);
        }
    }
}
