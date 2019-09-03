import java.io.*;

public class Ex3 {
	static int num_threads = 10;

	static class Ex3Thread implements Runnable {
		private int threadID;

		public Ex3Thread(int id){
			this.threadID = id;
		}

		public void run(){
			System.out.println("Hello World! It's me, thread #" + threadID);
			try {
				Thread.sleep(500);
			} catch(InterruptedException e){
			}
		}
	}

	public static void main(String[] args) {
		int i;

		for (i = 0; i < num_threads; i++){
			Thread t = new Thread(new Ex3Thread(i));
			t.start();
		}
	}
}
