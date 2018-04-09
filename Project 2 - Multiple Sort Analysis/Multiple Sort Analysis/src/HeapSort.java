/**
 * COMP215-Programming Project 2: Multiple Sort Analysis.
 * HEAPSORT is the Java implementation of the heap sort algorithm.
 * This implementation is based on psuedocode from "CLRS Algorithms."
 * This class is timed using the STOPWATCH class.
 * @author Andrew Parsons
 * @version 27 February 2017
 */
class HeapSort implements Sorter {

    /* --- INSTANCE VARIABLES --- */
    private Stopwatch stopwatch;
    private long elapsedTime;
    private static boolean debug = MainApp.debug;
    private static int heapSize;

    @Override
    public Comparable[] sort(Comparable[] dataset) {

        stopwatch = new Stopwatch();

        buildMaxHeap(dataset);
        for (int i = dataset.length-1; i >= 0; i--) {
            swap(dataset, 0, i);
            heapSize = heapSize - 1;
            maxHeapify(dataset,0,heapSize);
        }

        elapsedTime = stopwatch.elapsedTime();
        return dataset;
    }

    private void buildMaxHeap(Comparable[] dataset) {

        heapSize = dataset.length - 1;
        /*INIT: everything is a leaf, so everything is a max-heap */
        if (debug)
            assert assertionIsMaxHeap(dataset, heapSize);
        int i;
        for (i = heapSize / 2; i >= 0; i--) {
            maxHeapify(dataset, i, heapSize);
            /*MAIN: maxHeapify preserves invariant*/
            if (debug)
                assert assertionIsMaxHeap(dataset, i);
        }
        /*TERM: when i==0, all nodes are max-heaps */
        if (debug) {
            assert assertionIsMaxHeap(dataset,i);
        }
    }

    private void maxHeapify(Comparable[] dataset, int i, int heapMaxIndex) {
        int left = leftIndex(i);
        int right = rightIndex(i);
        int largest = i;
        if (left < heapMaxIndex && dataset[left].compareTo(dataset[i]) > 0) {

            largest = left;
        }
        if (right < heapMaxIndex && dataset[right].compareTo(dataset[largest]) > 0) {
            largest = right;
        }
        if (largest != i) {
            swap(dataset, i, largest);
            maxHeapify(dataset, largest, heapMaxIndex);
        }
    }

    private void swap(Comparable[] dataset, int a, int b) {
        Comparable z = dataset[a];
        dataset[a] = dataset[b];
        dataset[b] = z;
    }

    private static int parentIndex(int i) {
        return (i - 1) / 2;
    }
    private static int leftIndex(int i) {
        return 2 * i + 1;
    }
    private static int rightIndex(int i) {
        return 2 * i + 2;
    }

    public long getElapsedTime() {
        return elapsedTime;
    }

    /** check if subarray is sorted in ascending order (called by assert) */
    private static boolean assertionIsMaxHeap(Comparable[] dataset, int index) {
        if (dataset[index].compareTo(dataset[index*2]) == -1) {
            return false;
        } return true;
    }

    @Override // DO NOT USE THIS METHOD
    public Comparable[] sort(Comparable[] dataset, int indexBegin, int indexEnd) {
        return new Comparable[0];
    }
}
