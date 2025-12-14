
namespace AdventOfCode2025.Days.Day10
{

    public struct Button
    {
        public int buttonMask;
        public Button(int mask)
        {
            buttonMask = mask;
        }
    }

    public class Machine
    {
        public int LightMask;
        public List<Button> Buttons;
        public List<int> Joltages;

        public Machine(string schematic) 
        {
            Buttons = new List<Button>();
            var diagrams = schematic.Split(' ');
            Joltages = new List<int>();
            foreach (var diagram in diagrams)
            {
                if (diagram[0] == '[')
                {
                    ParseLight(diagram);
                }
                else if (diagram[0] == '(')
                {
                    AddButton(diagram);
                }
                else
                {
                    Joltages = diagram.Substring(1, diagram.Length - 2).Split(',').Select(int.Parse).ToList();
                }
            }
            Buttons.Sort((a, b) => a.buttonMask.CompareTo(b.buttonMask));
        }

        public int MinButtonPresses()
        {
            Dictionary<int, int> stepsToMask = new Dictionary<int, int>();
            List<int> masks = new List<int>();
            masks.Add(0);
            stepsToMask[0] = 0;
            foreach(var button in Buttons)
            {
                int maskLength = masks.Count;
                for(var i = 0; i < maskLength; i++)
                {
                    int mask = masks[i];
                    int newMask = mask ^ button.buttonMask;
                    if(!stepsToMask.ContainsKey(newMask))
                    {
                        masks.Add(newMask);
                        stepsToMask.Add(newMask, stepsToMask[mask] + 1);
                    }
                    else if(stepsToMask[newMask] > stepsToMask[mask] + 1)
                    {
                        stepsToMask[newMask] = stepsToMask[mask] + 1;
                    }
                }
            }
            return stepsToMask[LightMask];
        }

        public int MinButtonPressesForJoltage()
        {
            int[,] matrix = new int[Buttons.Count, Joltages.Count]; 
            
            for(var i = 0; i < Joltages.Count; i++) 
            {
                for (var j = 0; j < Buttons.Count; j++)
                {
                    if ((Buttons[j].buttonMask & (1<<i)) > 0)
                    {
                        matrix[j, i] = 1;
                    }
                }
            }

            LEMatrix mat = new LEMatrix(matrix, Joltages.ToArray());

            int maxJoltages = Joltages.Max();
            List<int> maxPressesPerVariable = new List<int>();
            foreach (var freeVariable in mat.freeVariables)
            {
                int variableMaxPresses = maxJoltages;
                for(var j = 0; j < Joltages.Count; j++)
                {
                    if ((Buttons[freeVariable].buttonMask & (1 << j)) > 0)
                    {
                        variableMaxPresses = Math.Min(variableMaxPresses, Joltages[j]);
                    }
                }
                maxPressesPerVariable.Add(variableMaxPresses);
            }
            int freeVariablesCount = mat.freeVariables.Count;
            int poss = 1;
            List<int> fvValues = new List<int>();
            for (var i = 0; i < freeVariablesCount; i++)
            {
                poss *= (maxPressesPerVariable[i] + 1);
                fvValues.Add(0);
            }

            int lowest = -1;

            for(var i = 0; i <= poss; i++)
            {
                var result = mat.Solve(fvValues);
                if (result != null)
                {
                    int sum = result.Sum();
                    if (lowest == -1)
                    {
                        lowest = sum;
                    }
                    else
                    {
                        lowest = Math.Min(lowest, sum);
                    }
                }

                bool add = i < poss - 1;
                int addingTo = 0;
                while(add)
                {
                    add = false;
                    fvValues[addingTo] += 1;
                    if(fvValues[addingTo] > maxPressesPerVariable[addingTo])
                    {
                        fvValues[addingTo] = 0;
                        addingTo++;
                        add = true;
                        if(addingTo >= fvValues.Count)
                        {
                            break;
                        }
                    }
                }
            }

            return lowest;
        }

        private void ParseLight(string lightDiagram)
        {
            var lights = lightDiagram.Substring(1, lightDiagram.Length - 2).Select(c => c == '#' ? 1 : 0).ToList();
            int lightMask = 0;
            for (var i = 0; i < lights.Count; i++)
            {
                lightMask += (1 << i) * lights[i];
            }
            LightMask = lightMask;
        }

        private void AddButton(string buttonDiagram)
        {
            buttonDiagram = buttonDiagram.Substring(1, buttonDiagram.Length - 2);
            var ligthIndices = buttonDiagram.Split(',').Select(int.Parse).ToList();
            int buttonMask = 0;
            foreach(var ligth in ligthIndices)
            {
                buttonMask += (1 << ligth);
            }
            Buttons.Add(new Button(buttonMask));
        }
    }
}
