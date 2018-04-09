import static java.lang.String.valueOf;

/**
 * COMP215-Programming Project 2: Multiple Sort Analysis.
 * TESTRESULT encapsulates data from testing as a single (x,y) point.
 * X is _n_ , the size of the array.
 * Y is _T(n)_ , the mean calculation time to sort _n_ elements.
 * @author Andrew Parsons
 * @version 06 March 2017
 * (package-private)
 */
class TestResult {

    /* --- VARIABLES --- */

    int sizeOfArray;
    long meanTime;

    /* --- CONSTRUCTORS --- */

    /** (package-private): TESTRESULT constructs an object that holds the size of an array and the mean sorting time */
    TestResult(int sizeOfArray, long meanTime) {

        this.sizeOfArray = sizeOfArray;
        this.meanTime = meanTime;
    }

    /* --- METHODS --- */

    //getter methods

    String returnSizeOfArrayAsString(){
        return valueOf(sizeOfArray);
    }

    String returnMeanTimeAsString(){
        return valueOf(meanTime);
    }

    String returnMeanTimeAsDoubleString() {
        return valueOf((double) meanTime / 1E6);
    }
}
