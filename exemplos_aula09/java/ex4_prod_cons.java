import java.util.concurrent.*;

public class ex4_prod_cons {
	static int num_threads = 20;
	static int producers = 3;
	static int consumers = 3;
	static volatile int in = 0;
	static volatile int out = 0;
	static volatile int buffer[] = new int[num_threads];

	static class producer implements Runnable {
		Semaphore mutex;
		Semaphore empty;
		Semaphore full;
		private int tid;
		private int item = 0;

		public producer(int id, Semaphore mtx, Semaphore emp, Semaphore ful){
			this.tid = id;
			mutex = mtx;
			empty = emp;
			full = ful;
		}

		public void run(){
			while (true) {
				item++;
				try {
					empty.acquire();
					mutex.acquire();
					buffer[in] = item;
					System.out.println("produtor " + tid + " escrevendo na pos " + in);
					in = (in + 1) % num_threads;
					mutex.release();
					full.release();
				}catch (InterruptedException e) {
				}
			}
		}
	}

	static class consumer implements Runnable {
		Semaphore mutex;
		Semaphore empty;
		Semaphore full;
		private int tid;
		private int item = 0;

		public consumer(int id, Semaphore mtx, Semaphore emp, Semaphore ful){
			this.tid = id;
			mutex = mtx;
			empty = emp;
			full = ful;
		}

		public void run(){
			while (true) {
				item++;
				try {
					full.acquire();
					mutex.acquire();
					item = buffer[in];
					System.out.println("consumidor " + tid + " retirando da pos " + out);
					out = (out + 1) % num_threads;
					mutex.release();
					empty.release();
				}catch (InterruptedException e) {
				}
			}
		}
	}

	public static void main(String[] args) {
		Semaphore mutex = new Semaphore(1);
		Semaphore empty = new Semaphore(num_threads);
		Semaphore full = new Semaphore(0);
		int i;

		for (i = 0; i < producers; i++){
			Thread t = new Thread(new producer(i, mutex, empty, full));
			t.start();
		}
		for (i = 0; i < consumers; i++){
			Thread t = new Thread(new consumer(i, mutex, empty, full));
			t.start();
		}
	}
}
