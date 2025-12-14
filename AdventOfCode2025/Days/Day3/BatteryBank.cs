namespace AdventOfCode2025.Days.Day3
{
    class BatteryBank
    {
        List<int> Joltages;
        public BatteryBank(string batteryLine) 
        {
            Joltages = new List<int>();
            foreach (var c in batteryLine)
            {
                Joltages.Add(int.Parse(c.ToString()));
            }
        }

        public int BiggestBankJoltage()
        {
            int maxJoltageIndex = 0;
            for (int i = 1; i < Joltages.Count - 1; i++)
            {
                if(Joltages[i] > Joltages[maxJoltageIndex])
                {
                    maxJoltageIndex = i;
                }
            }
            int secondMaxJoltage = maxJoltageIndex + 1;
            for (int i = maxJoltageIndex + 2; i < Joltages.Count; i++)
            {
                if (Joltages[i] > Joltages[secondMaxJoltage])
                {
                    secondMaxJoltage = i;
                }
            }
            return 10*Joltages[maxJoltageIndex]+Joltages[secondMaxJoltage];
        }
        public long BiggestOverrideBankJoltage()
        {
            List<int> maxIndices = new List<int>(12);
            int lastMaxIndex = -1;
            long result = 0;
            for(int k = 0; k < 12; k++)
            {
                maxIndices.Add(lastMaxIndex+1);
                for(int i = maxIndices[k]; i < Joltages.Count - 11 + k; i++)
                {
                    if (Joltages[i] > Joltages[maxIndices[k]])
                    {
                        maxIndices[k] = i;
                    }
                }
                lastMaxIndex = maxIndices[k];
                result *= 10;
                result += Joltages[maxIndices[k]];
            }

            return result;
        }
    }
}
