/**
 * COMP215-Programming Project 3: 01 Knapsack Problem Analysis.
 * KNAPSACKITEM is an object that the GreedySolution requires for operation. This class defines a select item's
 * value, weight, and price density. The price densities are comparable.
 * @author Andrew Parsons
 * @version 09 March 2017
 */
class KnapsackItem implements Comparable<KnapsackItem> {

    private double value;
    private double weight;
    private double priceDensity;

    KnapsackItem(double value, double weight) {

        this.value = value;
        this.weight = weight;
        this.priceDensity = (value / weight);
    }

    @Override
    public int compareTo(KnapsackItem k) {
        if (this.priceDensity < k.priceDensity) {
            return -1;
        } else if (this.priceDensity > k.priceDensity) {
            return 1;
        } return 0;
    }

    public double getValue() {
        return value;
    }

    public double getWeight() {
        return weight;
    }

    public double getPriceDensity() {
        return priceDensity;
    }
}

