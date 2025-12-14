namespace AdventOfCode2025.Helpers
{
    class Grid<T> where T : new()
    {
        private readonly T _defaultValue;
        private T[,] _values;
        private readonly bool _outline = true;
        public Grid(T[,] values, T defaultValue, bool outline = true)
        {
            _outline = outline;
            _defaultValue = defaultValue;
            _values = new T[values.GetLength(0) + (outline ? 2 : 0), values.GetLength(1) + (outline ? 2 : 0)];
            int off = outline ? 1 : 0;
            for (int i = 0; i < values.GetLength(0); i++)
            {
                for (int j = 0; j < values.GetLength(1); j++)
                {
                    _values[i+off,j+off] = values[i,j];
                }
            }
        }

        public Grid(T[,] values, bool outline = true) : this(values, new(), outline){ }


    }
}
