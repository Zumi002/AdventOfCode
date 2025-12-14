namespace AdventOfCode2025.Days.Day12
{
    public class Present
    {
        public enum Rotation
        {
            R0 = 0,
            R90 = 1,
            R180 = 2,
            R270 = 3 // clockwise
        }
        Row[,] presentRows = new Row[4,3];
        
        public Present(List<string> lines)
        {
            for (var i = 0; i < Rot(Rotation.R270); i++)
            {
                for (var j = 0; j < 3; j++)
                {
                    presentRows[i, j] = new Row();
                }
            }
            for (var i = 0; i < 3; i++)
            {
                for(var j = 0; j < 3; j++)
                {
                    if (lines[i][j] == '#')
                    {
                        presentRows[Rot(Rotation.R0), i] = presentRows[Rot(Rotation.R0), i].On(j);
                        presentRows[Rot(Rotation.R90), j] = presentRows[Rot(Rotation.R90), j].On(2 - i);
                        presentRows[Rot(Rotation.R180), 2 - i] = presentRows[Rot(Rotation.R180), 2 - i].On(2 - j);
                        presentRows[Rot(Rotation.R270), 2 - j] = presentRows[Rot(Rotation.R270), 2 - j].On(i);
                    }
                }
            }
        }

        public (bool fitted, Row r1, Row r2, Row r3) TryFit(Row r1, Row r2, Row r3, int j)
        {
            for (var i = 0; i < Rot(Rotation.R270); i++)
            {
                if (!r1.Collides(presentRows[i,0] << j) &&
                    !r2.Collides(presentRows[i, 1] << j) &&
                    !r3.Collides(presentRows[i, 2] << j))
                {
                    return (true, r1.Merge(presentRows[i, 0] << j), r2.Merge(presentRows[i, 1] << j), r3.Merge(presentRows[i, 2] << j));
                }

                // flip
                if (!r1.Collides(presentRows[i, 2] << j) &&
                    !r2.Collides(presentRows[i, 1] << j) &&
                    !r3.Collides(presentRows[i, 0] << j))
                {
                    return (true, r1.Merge(presentRows[i, 2] << j), r2.Merge(presentRows[i, 1] << j), r3.Merge(presentRows[i, 0] << j));
                }
            }

            return (false, r1, r2, r3);
        }

        public void Print(Rotation rot)
        {
            Console.WriteLine();
            for (var i = 0; i < 3; i++)
            {
                for (var j = 0; j < 3; j++)
                {
                    Console.Write(presentRows[Rot(rot), i].GetChar(j));
                }
                Console.WriteLine();
            }
        }

        public static int Rot(Rotation rot)
        {
            return (int)(rot);
        }
    }
}
