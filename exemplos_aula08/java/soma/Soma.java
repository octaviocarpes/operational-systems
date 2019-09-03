import java.util.concurrent.*;

class Soma {
	public static void main(String [] args){
		Semaphore m = new Semaphore(1);

		if (args.length > 0){
			if (Integer.parseInt(args[0]) < 0) {
				System.err.println(args[0] + "precisa ser >= 0.");
			} else {
				MutableInteger soma = new MutableInteger();

				int upper = Integer.parseInt(args[0]);

				soma.setZero();
				System.out.println("Sem mutex:");
				Thread thrd1 = new Thread(new Somatorio(upper, soma, m, 0));
				thrd1.start();
				Thread thrd2 = new Thread(new Somatorio(upper, soma, m, 0));
				thrd2.start();
				Thread thrd3 = new Thread(new Somatorio(upper, soma, m, 0));
				thrd3.start();
				try{
					thrd1.join();
					thrd2.join();
					thrd3.join();
					System.out.println("Soma Total: "+soma.getValue());
				}catch(InterruptedException e) {
				}
				soma.setZero();
				System.out.println("Com mutex:");
				thrd1 = new Thread(new Somatorio(upper, soma, m, 1));
				thrd1.start();
				thrd2 = new Thread(new Somatorio(upper, soma, m, 1));
				thrd2.start();
				thrd3 = new Thread(new Somatorio(upper, soma, m, 1));
				thrd3.start();
				try{
					thrd1.join();
					thrd2.join();
					thrd3.join();
					System.out.println("Soma Total: "+soma.getValue());
				}catch(InterruptedException e) {
				}
			}
		} else {
			System.err.println("Uso : Soma <Valor interior>");
		}
	}
}
