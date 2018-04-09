/**
 * COMP215-Programming Project 2: Multiple Sort Analysis.
 * STOPWATCH serves as a timer to calculate the nanosecond duration of performing a sort on an array.
 * @author Andrew Parsons
 * @version 06 March 2017
 * (package-private)
 */
class Stopwatch {

    /* --- VARIABLES --- */

    private final long timeStart;

    /* --- CONSTRUCTORS --- */

    /** (package-private): time is initialized upon creation */
    Stopwatch() { timeStart = System.nanoTime(); }

    /* --- METHODS --- */

    /** (package-private): time is returned as the current-initial */
    long elapsedTime() {
        return ( System.nanoTime() - timeStart);
    }
}