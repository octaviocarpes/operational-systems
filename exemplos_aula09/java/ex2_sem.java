import java.util.concurrent.*;

public class ex2_sem {
	static int num_threads = 10;
	static volatile int r = 0;

	static class ex2_thread implements Runnable {
		Semaphore s;
		private int tid;

		public ex2_thread(int id, Semaphore sem){
			this.tid = id;
			s = sem;
		}

		public void run(){
			while (true) {
				try {
					s.acquire();
					r++;
					System.out.println("thread " + tid + " acessando recurso.. (" + r + ")");
					Thread.sleep(100);
					System.out.println("thread " + tid + " liberando recurso.. (" + r + ")");
					r--;
					s.release();
					Thread.sleep(100);
				}catch (InterruptedException e) {
				}
			}
		}
	}

	public static void main(String[] args) {
		Semaphore sem = new Semaphore(3);
		int i;

		for (i = 0; i < num_threads; i++){
			Thread t = new Thread(new ex2_thread(i, sem));
			t.start();
		}

	}
}
