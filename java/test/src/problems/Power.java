package problems;

public class Power {
	private long powerLast10(int x, int n) {
		if (x == 0) {
			return 0;
		}
		if (x < 0) {
			x = -x;
		}
		long res = 1 , y = x;
		while (n > 0) {
			if (n % 2 == 1) {
				res = productLast10(res, y);
			}
			y = productLast10(y, y);
			n = n / 2;
		}
		return res; 
	}
	
	private long productLast10(long a, long b) {
		long a1 = a / 100000000, b1 = b / 100000000;
		long a2 = a % 100000000, b2 = b % 100000000;
		long res = a2 * b2 % 10000000000L + a1 * b2 % 100 * 100000000 + a2 * b1 % 100 * 100000000;
		return res % 10000000000L;
	}
	
	public static void main(String[] args) {
		Power p = new Power();
		System.out.println(p.powerLast10(2, 35));
	}
}
