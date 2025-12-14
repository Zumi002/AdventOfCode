namespace AdventOfCode2025.Days.Day9
{
    public class TiledFloor
    {
        SegmentTree<(long min, long max)> minMaxX;
        SegmentTree<(long min, long max)> minMaxY;
        List<(long x, long y)> RedTiles;
        public TiledFloor(List<(long x, long y)> redTiles) 
        {
            RedTiles = redTiles;
            var prevRedTile = RedTiles.First();
            (long min, long max) x = (prevRedTile.x, prevRedTile.x),
                y = (prevRedTile.y, prevRedTile.y);
            for(var i = 0; i < RedTiles.Count; i++)
            {
                x.min = Math.Min(x.min, RedTiles[i].x);
                x.max = Math.Max(x.max, RedTiles[i].x);
                y.min = Math.Min(y.min, RedTiles[i].y);
                y.max = Math.Max(y.max, RedTiles[i].y);
            }
            List<(long min, long max)> minMaxGreenX = Enumerable.Repeat((y.max, y.min), (int)x.max + 1).ToList();
            List<(long min, long max)> minMaxGreenY = Enumerable.Repeat((x.max, x.min), (int)y.max + 1).ToList();
            for (var i = 1; i < RedTiles.Count; i++)
            {
                var xStart = prevRedTile.x;
                var xEnd = RedTiles[i].x;
                if(xStart >= xEnd)
                {
                    (xStart, xEnd) = (xEnd, xStart);
                }
                var yStart = prevRedTile.y;
                var yEnd = RedTiles[i].y;
                if (yStart >= yEnd)
                {
                    (yStart, yEnd) = (yEnd, yStart);
                }
                for (var j = xStart; j <= xEnd; j++)
                {
                    minMaxGreenX[(int)j] = (Math.Min(minMaxGreenX[(int)j].min, yStart), Math.Max(minMaxGreenX[(int)j].max, yEnd));
                }
                for (var j = yStart; j <= yEnd; j++)
                {
                    minMaxGreenY[(int)j] = (Math.Min(minMaxGreenY[(int)j].min, xStart), Math.Max(minMaxGreenY[(int)j].max, xEnd));
                }
                prevRedTile = RedTiles[i];
            }

            var folding = ((long min, long max) a, (long min, long max) b) => (Math.Max(a.min, b.min), Math.Min(a.max, b.max));
            minMaxX = new SegmentTree<(long min, long max)>(minMaxGreenX, folding);
            minMaxY = new SegmentTree<(long min, long max)>(minMaxGreenY, folding);
        }

        public long BiggestConstrainedRectangleArea()
        {
            long biggestArea = 0;
            foreach (var tile1 in RedTiles)
            {
                foreach(var tile2 in RedTiles)
                {
                    var xStart = tile1.x;
                    var xEnd = tile2.x;
                    if (xStart >= xEnd)
                    {
                        (xStart, xEnd) = (xEnd, xStart);
                    }
                    var yStart = tile1.y;
                    var yEnd = tile2.y;
                    if (yStart >= yEnd)
                    {
                        (yStart, yEnd) = (yEnd, yStart);
                    }
                    var area = (xEnd - xStart + 1) * (yEnd - yStart + 1);
                    if (area < biggestArea)
                    {
                        continue;
                    }
                    var limitsY = minMaxX.GetInterval((int)xStart, (int)xEnd);
                    var limitsX = minMaxY.GetInterval((int)yStart, (int)yEnd);
                    if(limitsX.min > xStart || limitsX.max <  xEnd ||
                        limitsY.min > yStart || limitsY.max < yEnd)
                    {
                        continue;
                    }
                    biggestArea = area;
                }
            }

            return biggestArea;
        }
    }
}
