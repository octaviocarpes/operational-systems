import java.io.*;

public class Ex1 {
	static volatile int global = 20;

	static class Ex1Thread implements Runnable {
		public void run(){
			global = 40;

			System.out.println("Nova thread: " + global);
		}
	}

	public static void main(String[] args) {
		System.out.println("Thread principal: " + global);
		Thread t = new Thread(new Ex1Thread());
		t.start();
		try {
			t.join();
		} catch(Exception ex) {
		}
		System.out.println("Thread principal: " + global);

	}
}
