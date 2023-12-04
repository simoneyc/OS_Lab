public class lab2 {
	public static int count = 0;
	public static void main(String argv[]){
	ShareData s = new ShareData();
	Thread t1 = new Thread(s);
	Thread t2 = new Thread(s);
	Thread t3 = new Thread(s);
	Thread t4 = new Thread(s);

	t1.start();
	t2.start();
	t3.start();
	t4.start();
	try {
		t1.join();
		t2.join();
		t3.join();
		t4.join();
	} catch(InterruptedException ie) {
		System.err.println(ie);
	}

    System.out.println("Final count value: " + count);
    }
}

class ShareData implements Runnable {
   
	public void run() {
		for(int i=1; i<=250000; i++){
			lab2.count +=1;
		}
		System.out.println("Thread name is " + Thread.currentThread().getName() + ", count is: " + lab2.count);
	}
}
