/**
 * COMP215-Programming Project 3: 01 Knapsack Problem Analysis.
 * GREEDYSOLUTION is the Java implementation of the greedy algorithm to solve the 01 Knapsack Problem.
 * @author Andrew Parsons
 * @version 09 March 2017
 */
class GreedySolution implements Solution {

    /* --- INSTANCE VARIABLES --- */
    static double[] value;
    static double[] weight;

    /* --- METHODS -- */

    /**
     * KNAPSACK returns the solution to the 01 Knapsack Problem, using a greedy algorithm.
     * @param valuePass, the passed values
     * @param weightPass, the passed weights
     * @param capacity, the knapsack capacity
     * @return double, the best value taken
     */
    public double knapsack(double[] valuePass, double[] weightPass , double capacity) {

        if (valuePass.length == 0) { return 0; }
        value = valuePass;
        weight = weightPass;
        double valueTaken = 0;
        KnapsackItem[] knapsackItems = new KnapsackItem[value.length];

        for (int v = 0; v < value.length; v++) {
            knapsackItems[v] = new KnapsackItem(value[v], weight[v]);
        }

        KnapsackMain.quickSort.sort(knapsackItems,0,knapsackItems.length-1);
        double remainingCapacity = capacity;

        for (int n = knapsackItems.length-1; n >= 0; n--) {

            if (knapsackItems[n].getWeight() <= remainingCapacity) {

                valueTaken = valueTaken + knapsackItems[n].getValue();
                remainingCapacity = remainingCapacity - (knapsackItems[n].getWeight());
            }
        }
        return valueTaken;
    }
}