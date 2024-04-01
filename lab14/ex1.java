import java.lang.Thread;
//class job implements Runnable{
//	public synchronized void run(){
//		for(int i=0;i<25000000;i++)
//			ex1.c++;
//	}
//}

class inc implements Runnable {
	public synchronized void run() {
		for(int i = 0; i < 25000000; i++) {
			Sync.add();
		}
	}
}
class dec implements Runnable {
	public synchronized void run() {
		for(int i = 0; i < 25000000; i++) {
			Sync.sub();
		}
	}
}
public class ex1{
	public static int c = 0;
	public static void main(String[] args){
		inc i = new inc();
		dec d = new dec();
		Thread t1 = new Thread(i);
		Thread t2 = new Thread(i);
		Thread t3 = new Thread(d);
		Thread t4 = new Thread(d);
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		try{
			t1.join();
			t2.join();
			t3.join();
			t4.join();
		}catch(InterruptedException e){
		}
		Sync.show();
	}
}
class Sync {
	private static int count = 0;
	public static synchronized void add(){
		count++;
	}
	public static synchronized void sub(){
		count--;
	}
	public static synchronized void show(){
		System.out.println("Count = "+count);
	}
}
