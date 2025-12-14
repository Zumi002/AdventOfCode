using AdventOfCode2025.Helpers;

namespace AdventOfCode2025.Days.Day3
{
    public class Day3 : Day
    {
        public Day3() : base(3) { }
        public override void Test()
        {
            int sum = 0;
            long sumOverride = 0;
            foreach (var line in testFileReader.Lines)
            {
                BatteryBank batteryBank = new BatteryBank(line);
                int joltage = batteryBank.BiggestBankJoltage();
                sum += joltage;
                long overriddeJoltage = batteryBank.BiggestOverrideBankJoltage();
                Console.WriteLine($"Joltage: {joltage}, override: {overriddeJoltage}");
                sumOverride += overriddeJoltage;
            }
            Console.WriteLine($"Sum: {sum}\nSumOverride: {sumOverride}");
        }

        public override void Part1()
        {
            int sum = 0;
            foreach (var line in fileReader.Lines)
            {
                BatteryBank batteryBank = new BatteryBank(line);
                int joltage = batteryBank.BiggestBankJoltage();
                sum += joltage;
            }
            Console.WriteLine($"Sum: {sum}");
        }

        public override void Part2()
        {
            long sum = 0;
            foreach (var line in fileReader.Lines)
            {
                BatteryBank batteryBank = new BatteryBank(line);
                long overrideJoltage = batteryBank.BiggestOverrideBankJoltage();
                sum += overrideJoltage;
            }
            Console.WriteLine($"Sum: {sum}");
        }
    }
}
