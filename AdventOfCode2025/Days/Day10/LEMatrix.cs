namespace AdventOfCode2025.Days.Day10
{
    public class LEMatrix
    {
        public int[,] A;
        public int[] b;
        public List<int> freeVariables;
        int[] values;
        public LEMatrix(int[,] matrixA, int[] vectorB)
        {
            A = matrixA;
            b = vectorB;
            values = new int[A.GetLength(0)];
            freeVariables = new List<int>();
            GE(); 
            int lastX = -1;
            for (int y = 0; y < A.GetLength(1); y++)
            {
                for(int x = lastX+1;  x < A.GetLength(0); x++)
                {
                    if(A[x, y] == 0)
                    {
                        freeVariables.Add(x);
                        lastX = x;
                    }
                    else 
                    {
                        lastX = x;
                        break;
                    }
                }
            }
            for(int x = lastX+1; x < A.GetLength(0); x++)
            {
                freeVariables.Add(x);
            }
        }

        public void GE()
        {
            int settingY = 0;
            for (int x = 0; x < A.GetLength(0); x++)
            {
                bool isXLock = false;
                for (int y = settingY; y < A.GetLength(1); y++)
                {
                    if (A[x,y] != 0 && !isXLock)
                    {
                        isXLock = true;
                        if (A[x, y] < 0)
                        {
                            MultiplyRow(y, -1);
                        }
                        if (settingY != y)
                        {
                            SwapRow(settingY, y);

                        }
                    }
                    else if (A[x, y] != 0)
                    {
                        ReduceRow(settingY, y, x);
                    }
                }
                if(isXLock)
                {
                    settingY++;
                    if(settingY >= A.GetLength(1))
                    {
                        break;
                    }
                }
            }
        }

        public void SwapRow(int row1, int row2)
        {
            for(int x = 0;  x < A.GetLength(0); x++)
            {
                (A[x, row1], A[x, row2]) = (A[x, row2], A[x, row1]);
            }
            (b[row1], b[row2]) = (b[row2], b[row1]);
        }

        public void ReduceRow(int baseRow, int row, int leadingX)
        {
            if (A[leadingX, baseRow] < 0)
            {
                MultiplyRow(baseRow, -1);
            }
            int mul = A[leadingX, row];
            MultiplyRow(row, A[leadingX, baseRow]);
            for(int x = leadingX; x < A.GetLength(0); x++)
            {
                A[x, row] -= A[x, baseRow] * mul;
            }
            b[row] -= b[baseRow] * mul;
        }
        
        public void MultiplyRow(int row, int scalar)
        {

            for (int x = 0; x < A.GetLength(0); x++)
            {
                A[x, row] *= scalar;
            }
            b[row] *= scalar;
        }

        public List<int>? Solve(List<int> fVValues)
        {
            if(freeVariables.Count != fVValues.Count)
            {
                return null;
            }
            
            for (int i = 0; i < A.GetLength(0); i++)
            {
                values[i] = -1;
            }
            for (int i = 0; i < freeVariables.Count; i++)
            {
                values[freeVariables[i]] = fVValues[i];
            }

            for (int y = A.GetLength(1) - 1; y >= 0; y--)
            {
                int rowSum = 0;
                int gettingValueFor = -1;
                for(int x = 0; x < A.GetLength(0); x++)
                {
                    if (A[x, y] != 0 && gettingValueFor == -1)
                    {
                        gettingValueFor = x;
                    }
                    else if (A[x, y] != 0)
                    {
                        if (values[x] == -1)
                        {
                            return null;
                        }
                        rowSum += values[x]*A[x, y];
                    }
                }
                var value = b[y] - rowSum;
                if(gettingValueFor == -1)
                {
                    continue;
                }
                if(value < 0 || value % A[gettingValueFor, y] != 0)
                {
                    return null;
                }
                values[gettingValueFor] = value / A[gettingValueFor, y];
            }

            return values.ToList();
        }
    }
}
