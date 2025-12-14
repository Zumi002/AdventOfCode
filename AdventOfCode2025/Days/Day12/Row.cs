namespace AdventOfCode2025.Days.Day12
{
    public struct Row
    {
        public ulong row;

        public Row(ulong row)
        {
            this.row = row;
        }

        public Row Merge(Row anotherRow)
        {
            return new Row(row | anotherRow.row);
        }

        public Row Subtract(Row anotherRow)
        {
            var mask = Full().row ^ anotherRow.row;
            return new Row(row & mask);
        }

        public bool Collides(Row anotherRow)
        {
            return (row & anotherRow.row) != 0;
        }

        public Row On(int pos)
        {
            return new Row(row | ((ulong)1 << pos));
        }

        public Row Off(int pos)
        {
            return new Row(row & (Full().row ^ ((ulong)1 << pos)));
        }
        
        public static Row operator<<(Row r, int  pos)
        {
            return new Row(r.row << pos);
        }

        public static Row operator>> (Row r, int pos)
        {
            return new Row(r.row >> pos);
        }

        public static Row Full()
        {
            return new Row(ulong.MaxValue);
        }

        public char GetChar(int pos)
        {
            if(IsSet(pos))
            {
                return '#';
            }
            return '.';
        }

        public bool IsSet(int pos)
        {
            return (row & ((ulong)1 << pos)) > 0;
        }
    }
}
