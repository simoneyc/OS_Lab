import java.util.concurrent.locks.*;
import java.lang.Thread;

public class ex2 {
	public static Warehouse ware = new Warehouse();
	
	public static void main(String[] args) {
		job_set set = new job_set();
		job_get get = new job_get();
		Thread t1 = new Thread(set);
		Thread t2 = new Thread(get);
		
		t2.start();
		t1.start();
		
		
		try {
			t1.join();
			t2.join();
		}
		catch(InterruptedException e) {} 
	}

	static class job_set implements Runnable {
		public void run() {
			while(true){
				ware.setProduct();
			}
		}
	}

	static class job_get implements Runnable {
		public void run() {
			while(true) {
				ware.getProduct();
			}
		}
	}
}

class Warehouse {
	private Lock lock = new ReentrantLock();
	private Condition threadCond = lock.newCondition();
	
	private int product = 0;
	
	public void setProduct() {
		lock.lock();
		try {
			while(product == 10) {
				try {
					System.out.printf("FULL %n");
					threadCond.await();
				}
				catch(InterruptedException e) {e.printStackTrace();}
			}
			product = product + 1;
			System.out.printf("product +1 / Amount= %d %n",product);
			
			threadCond.signal();
		}
		finally {
			lock.unlock();
		}
	}
	
	public void getProduct() {
		lock.lock();
		try {
			while(product == 0) {
				try {
					System.out.printf("EMPTY %n");
					threadCond.await();
				}
				catch(InterruptedException e) {e.printStackTrace();}
			}
			product = product - 1;
			System.out.printf("product -1 / Amount= %d %n",product);
			
			threadCond.signal();
		}
		finally {
			lock.unlock();
		}
	}
}

