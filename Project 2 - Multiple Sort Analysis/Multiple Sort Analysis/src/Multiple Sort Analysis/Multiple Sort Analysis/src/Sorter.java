/**
 * COMP215-Programming Project 2: Multiple Sort Analysis.
 * SORTER is an interface for sorting algorithms.
 * @author Andrew Parsons
 * @version 27 February 2017
 */
interface Sorter {

    Comparable[] sort(Comparable[] dataset);

    Comparable[] sort(Comparable[] dataset, int indexBegin, int indexEnd);

    long getElapsedTime();

}
