package problems;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Maze {
    public static class Point {
        public int x;
        public int y;
        public Point(int xx, int yy) {x = xx; y = yy;};
        public void print() {
            System.out.print("(" + x + "," + y + ") ");
        }
        public boolean equals(Object ap) {
            if (!(ap instanceof Point)) {
                return false;
            }
            Point aap = (Point)ap;
            return x == aap.x && y == aap.y;
        }
        public int hashCode() {
            return 13^x + 29 ^ y;
        }
    }
    
    private boolean inRange(int[][] maze, Point p) {
        return p.x >= 0 && p.y >= 0 && p.x < maze.length && p.y < maze[0].length;
    }
    
    private ArrayList<Point> getNexts(int[][] maze, boolean[][] isVisited, Point curr) {
        ArrayList<Point> res = new ArrayList<Point>();
        int[] dx = new int[]{-1, 0, 1, 0}, dy = new int[]{0, -1, 0, 1};
        for (int i = 0; i < 4; i++) {
            Point tmp = new Point(curr.x + dx[i], curr.y + dy[i]);
            if (inRange(maze, tmp) && !isVisited[tmp.x][tmp.y] && maze[tmp.x][tmp.y] != 1) {
                res.add(tmp);
            }
        }
        return res;
    }
    
    /**
     * find the shortest path to go fromo s to p in maze
     * 0 in maze means ok, 1 mean obstacle
     * @param maze
     * @param s
     * @param p
     * @return
     */
    int findShortestPath(int[][] maze, Point s, Point t) {
        if (maze == null || maze.length == 0 || maze[0].length == 0) {
            return -1;
        }
        if (!inRange(maze, s) || !inRange(maze, t)) {
            return -1;
        }
        if (maze[s.x][s.y] == 1 || maze[t.x][t.y] == 1) {
            return -1;
        }
        List<Point> q1 = new LinkedList<Point>(), q2 = new LinkedList<Point>();
        q1.add(s);
        HashMap<Point, Point> m = new HashMap<Point, Point>();
        boolean[][] isVisited = new boolean[maze.length][maze[0].length];
        Point curr = s;
        while (!q1.isEmpty()) {
            curr = q1.get(0);
            q1.remove(0);
            isVisited[curr.x][curr.y] = true;
            if (curr.equals(t)) {
                break;
            }
            ArrayList<Point> nexts = getNexts(maze, isVisited, curr);
            for (Point p : nexts) {
                q2.add(p);
                m.put(p, curr);
                
            }
            if (q1.isEmpty()) {
                List<Point> tmp = q1;
                q1 = q2;
                q2 = tmp;
            }
        }
        if (!curr.equals(t)) {
            return -1;
        }
        ArrayList<Point> res = new ArrayList<Point>();
        while (!curr.equals(s)) {
            res.add(curr);
            curr = m.get(curr);
        }
        res.add(s);
        Collections.reverse(res);
        for (Point p : res) {
            p.print();
        }
        return res.size();
    }
    
    public static void main(String[] args) {
        int[][] maze = new int[][] {{0,0,0,0,1}, {0,0,1,0,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,1,0,0,0}};
        Maze m = new Maze();
        Point p = new Point(4, 0), q = new Point(2, 4);
        System.out.println(m.findShortestPath(maze, p, q));
    }

}
