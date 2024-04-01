import java.util.concurrent.*;
import java.util.*;

public class final_2 extends RecursiveAction {
	int little;
	int big;
	int arr[];

	final_2(int[] arr, int little, int big) {
		this.arr = arr;
		this.little = little;
		this.big = big;
	}
	public static void main(String args[]) {
		int[] arr = new int[20];
		int count = 0;
		Random rand = new Random();
		Set<Integer> set = new HashSet<>();

		for (int i = 0; i < 20; i++) {
            		int num;
		    do {
		        num = rand.nextInt(100) + 1;
		    } while (!set.add(num));
		    arr[i] = num;
        	}

		ForkJoinTask <Void> task = new final_2(arr, 0, arr.length-1);
		ForkJoinPool pool = new ForkJoinPool();
		pool.invoke(task);

		System.out.println("Array: ");
		for(int i = 0; i < 20; i++) {
			System.out.print(arr[i]);
			System.out.print(" ");
			if(arr[i] > 50){
				count++;
			}
		}
		System.out.println();
		System.out.printf("Number of elements greater than 50: %d",count);
		System.out.println();
	}

	protected void compute() {
		if(little < big) {
			int mid = (little+big) / 2;
			final_2 m1 = new final_2(arr, little, mid);
			final_2 m2 = new final_2(arr, mid+1, big);
			invokeAll(m1, m2);
		}
	}
}

