package problems;

import java.util.HashMap;

public class MaxPointOnLine {
    public static class Point {
        public int x;
        public int y;
        public Point() { x = 0; y = 0; }
        public Point(int a, int b) { x = a; y = b; }
    }
    
    public int maxPoints(Point[] points) {
        if (points.length < 2) {
            return points.length;
        }
        int maxCount = 0;
        for (int i = 0; i < points.length; i++) {
            int vCount = 0, dup = 0;
            HashMap<Double, Integer> m = new HashMap<Double, Integer>();
            for (int j = i + 1; j < points.length; j++) {
                if (points[i].x == points[j].x && points[i].y == points[j].y) {
                    dup++;
                    continue;
                }
                if (points[i].x == points[j].x) {
                    vCount++;    
                    continue;
                }
                // Java has this +0.0 and -0.0 problem
                Point pa = points[i], pb = points[j];
                if (pa.x < pb.x) {
                    Point pc = pa;
                    pa = pb;
                    pb = pc;
                }
                // stupid int to double conversion!
                double slope = (Double.valueOf(pb.y) - pa.y) / (pb.x - pa.x);
                if (m.containsKey(slope)) {
                    m.put(slope, m.get(slope) + 1);
                } else {
                    m.put(slope, 1);
                }
            }
            dup++;
            vCount += dup;
            maxCount = maxCount > vCount ? maxCount : vCount;
            for (int p : m.values()) {
                p += dup;
                maxCount = p > maxCount ? p: maxCount;
            }
        }
        
        return maxCount;
    }
    
    public static void main(String[] args) {
       Point[] p = new Point[]{new Point(2, 3), new Point(3, 3), new Point(-5, 3)};
       MaxPointOnLine M = new MaxPointOnLine();
       System.out.println(M.maxPoints(p));
       p = new Point[]{new Point(84,250),new Point(0,0),new Point(1,0),new Point(0,-70),new Point(0,-70),new Point(1,-1),new Point(21,10),new Point(42,90),new Point(-42,-230)};
       System.out.println(M.maxPoints(p));
    }
}
