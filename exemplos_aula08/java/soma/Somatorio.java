import java.util.concurrent.*;

class Somatorio implements Runnable {
	private int upper;
	private MutableInteger ValorSoma;
	private Semaphore mutex;
	private int lock;

	public Somatorio(int upper, MutableInteger ValorSoma, Semaphore m, int with_lock) {
		this.upper = upper;
		this.ValorSoma = ValorSoma;
		this.lock = with_lock;
		mutex = m;
	}

	public void run() {
		if (lock == 0) {
			for (int i = 0; i < upper; i++) {
				ValorSoma.setValue(ValorSoma.getValue() + 1);
			}
		} else {
			for (int i = 0; i < upper; i++) {
				try{
					mutex.acquire();
					ValorSoma.setValue(ValorSoma.getValue() + 1);
					mutex.release();
				}catch (InterruptedException e){
				}
			}
		}
	}
}
