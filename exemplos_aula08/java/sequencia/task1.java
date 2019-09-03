import java.util.concurrent.*;

public class task1 implements Runnable{
	Semaphore local, dependente;

	task1 (Semaphore m1, Semaphore m2){
		local = m1;
		dependente = m2;
	}

	public void run(){
		while (true) {
			try {
				local.acquire();
				System.out.println("task 1");
				Thread.sleep(100);
				dependente.release();
			}catch (InterruptedException e) {
			}
		}
	}
}
