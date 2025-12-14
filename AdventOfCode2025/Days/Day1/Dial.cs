namespace AdventOfCode2025.Days.Day1
{
    public class Dial
    {
        public int Position;
        public int NumberOfValues;
        public int Clicks;

        public Dial(int position = 0, int numberOfValues = 100)
        {
            Position = position;
            NumberOfValues = numberOfValues;
        }

        public int RotateLeft(int number)
        {
            int rots = number/NumberOfValues;
            int backward = (number % NumberOfValues);
            if (Position == 0) 
            {
                Position += NumberOfValues;
            }
            Clicks += rots + (backward >= Position ? 1 : 0);
            Position += NumberOfValues - backward;
            Position %= NumberOfValues;
            return Position;
        }

        public int RotateRight(int number)
        {
            int rots = number/NumberOfValues;
            int forward = number % NumberOfValues;
            Clicks += rots + (NumberOfValues <= Position + forward ? 1 : 0);
            Position += forward;
            Position %= NumberOfValues;
            return Position;
        }
    }
}
