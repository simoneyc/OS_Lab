import java.util.concurrent.*;
import java.util.*;

public class ParallelMergeSort extends RecursiveAction {
	int little;
	int big;
	int arr[];

	ParallelMergeSort(int[] arr, int little, int big) {
		this.arr = arr;
		this.little = little;
		this.big = big;
	}
	public static void main(String args[]) {
		int[] arr = new int[100];
		Random rand = new Random();
		//===
		Set<Integer> set = new HashSet<>();
		
		//System.out.println("------------");
		for (int i = 0; i < 100; i++) {
            		int num;
		    do {
		        num = rand.nextInt(100) + 1;
		    } while (!set.add(num));
		    arr[i] = num;
		    //System.out.println(arr[i]);
        	}
        	//===

		ForkJoinTask <Void> task = new ParallelMergeSort(arr, 0, arr.length-1);
		ForkJoinPool pool = new ForkJoinPool();
		pool.invoke(task);

		System.out.println("------------");
		for(int i = 0; i < 100; i++) {
			System.out.println(arr[i]);
		}
	}

	protected void compute() {
		if(little < big) {
			int mid = (little+big) / 2;
			ParallelMergeSort m1 = new ParallelMergeSort(arr, little, mid);
			ParallelMergeSort m2 = new ParallelMergeSort(arr, mid+1, big);
			invokeAll(m1, m2);
			merge(arr, little, mid, big);
		}
	}

	static void merge(int[] arr, int little, int mid, int big) {
		int[] tmp = new int[arr.length];
		for(int i = little; i <= big; i++) {
			tmp[i] = arr[i];
		}

		int i = little, j = mid+1, k = little;
		while(i <= mid && j <= big) {
			if(tmp[i] <= tmp[j]) {
				arr[k] = tmp[i];
				i++;
			}
			else {
				arr[k] = tmp[j];
				j++;
			}
			k++;
		}
		while(i <= mid) {
			arr[k] = tmp[i];
			i++;
			k++;
		}
		while(j <= big) {
			arr[k] = tmp[j];
			j++;
			k++;
		}
	}

}

