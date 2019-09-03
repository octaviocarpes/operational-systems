import java.util.concurrent.*;

public class Sequencia {
	public static void main(String[] args) {
		Semaphore mutex1 = new Semaphore(1);
		Semaphore mutex2 = new Semaphore(0);
		Semaphore mutex3 = new Semaphore(0);

		Thread t1 = new Thread(new task1(mutex1, mutex2));
		t1.start();

		Thread t2 = new Thread(new task2(mutex2, mutex3));
		t2.start();

		Thread t3 = new Thread(new task3(mutex3, mutex1));
		t3.start();
	}
}
