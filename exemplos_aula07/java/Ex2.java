import java.io.*;

public class Ex2 {
	static class Ex2Thread implements Runnable {
		public void run(){
			while (true) {
				System.out.print("x");
			}
		}
	}

	public static void main(String[] args) {
		Thread t = new Thread(new Ex2Thread());
		t.start();

		while (true) {
			System.out.print("o");
		}

	}
}
