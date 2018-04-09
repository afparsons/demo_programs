import java.util.Random;

/**
 * COMP215-Programming Project 2: Multiple Sort Analysis.
 * DATAGENERATOR creates a new array and fills it with random data
 * @author Andrew Parsons
 * @version 21 January 2017
 * (package-private)
 */
class DataGenerator {

    /**
     * CREATEDATASET is the constructor that returns a random array
     * @param size, the length of the array
     * @param maxValue, the maximum value of a randomly generated integer
     * @return dataset, an array filled with random data
     */
    Comparable[] createDataSet(int size, int maxValue) {

        Comparable[] dataset = new Comparable[size];
        Random rand = new Random();

        for (int i = 0; i < size; i++) {
            dataset[i] = rand.nextInt(maxValue);
        }
        return dataset;
    }
}
