/**
 * Car Wash Simulation Project:  CarWashSimulation Class
 * The Car Wash Simulation Project is described in
 * <a href="http://max.cs.kzoo.edu/cs210/Labs/Queues/CarWashProgram.html">Car
 * Wash Project Description</a>.
 * Authors: Autumn C. Spaulding and Alyce Brady. Based on a description by <a href="mailto:trollend@nb.net">Todd Ollendyke</a>.
 * Date:      13 July 2000
 * Modified:  12 October 2000: Separated simulation behavior from main into the CarWashSimulation class.
 * Modified:  29 October 2002: Separated class templates into separate files.
 * Modified:  27 October 2003: Set up waitingLine to use LLQueue instead of QueueVector
 * @author Andrew Parsons
 * @version 03 May 2016
 */

import java.util.Random;

/**
 *  CarWashSimulation manages the simulation of cars arriving at a car wash, waiting in line,
 *  and going through the wash cycle.
 */
public class CarWashSimulation
{
    private int currentTime;                // how many minutes the car wash has been open
    private int closingTime;                // when the car wash should close
    private int numOverTen;                 // how many cars wait more than 10 minutes
    private int arrayIndex;                 // index of array

    private double totalWaitingTime;        // total time spent waiting by all cars
    private double numCars;                 // how many cars were washed
    private double printedAverageWaitTime;  // rounded and truncated average wait time

    private Bay bay;                        // car wash bay
    private KQueue waitingLine;             // line of cars waiting to be washed
    private Random randGen;                 // random number generator
    private int[] waitTimeArray;            // array of wait times


    /** Construct a car wash simulation object. */
    public CarWashSimulation ()
    {
        bay = new Bay(CarWashApplication.BAY_TIME);
        waitingLine = new LLQueue<Car>();
        randGen = new Random();
        reset();
    }

    /** Reset the state of the simulation for a new run. */
    private void reset()
    {
        // reset everything to zero
        currentTime = 0;
        closingTime = 0;
        totalWaitingTime = 0;
        numCars = 0;
        numOverTen = 0;
        arrayIndex = 0;
        printedAverageWaitTime = 0;
        double arraySize = ((CarWashApplication.DAY_LENGTH) * ((1.0) / CarWashApplication.CHANCE_INT)) + ((CarWashApplication.DAY_LENGTH) * ((1.0) / CarWashApplication.CHANCE_INT)) * ((1.0) / CarWashApplication.CHANCE_INT);
        waitTimeArray = new int[(int) arraySize];
        bay.reset();

        // remove all waiting cars
        while ( ! waitingLine.isEmpty() )
        {
            Object o = waitingLine.dequeue();
        }
    }

    /** Run the simulation for a specified number of minutes (or whatever the
     *  unit for a single step of the simulation is).
     *  @param minutesToRun the number of steps of the simulation to run
     */    
    public double run (int minutesToRun)
    {
        // set closing time to DAY_LENGTH
        closingTime = minutesToRun;

        // step while the current time is before the closing time
        while (currentTime < closingTime)
            this.step();

        // wash the remaining cars after closing time, but do not take any new cars into the waitingLine
        while (!waitingLine.isEmpty())
        {
            if (bay.isEmpty())
            {
                bay.startWash();
                Car car = (Car) waitingLine.dequeue();
                waitTimeArray[arrayIndex] = currentTime - (car.arrivalTime());
                arrayIndex++;
            }
            if (!bay.isEmpty())
                bay.keepWashing();

            currentTime++;
        }

        // --- CLOSING TASK --- //
        for (int time : waitTimeArray)
        {
            if (time >= 10)
                numOverTen++;
            totalWaitingTime += time;
        }

        // prepare a legible #.## double
        double averageWaitTime = totalWaitingTime / numCars;
        printedAverageWaitTime = Math.round(averageWaitTime * 100);
        printedAverageWaitTime = printedAverageWaitTime / 100;

        // print the simulation results
        System.out.println("--------------------------------------------------------------------------------");
        System.out.println("Bay Wash Time: " + bay.getTimeToWashACar() + "  |  Total Num Cars: " + numCars + "  |  Total Waiting Time: " + totalWaitingTime + " minutes");
        System.out.println("Average Wait Time: " + printedAverageWaitTime + " minutes  |  Number of Cars Waiting 10+ minutes: " + numOverTen + " car(s)");
        System.out.println("________________________________________________________________________________");
        System.out.println();

        // prepare for new simulation
        this.reset();

        // return the day's average wait time for calculation of the weekly average wait time
        return averageWaitTime;
    }

    /** Execute a single step of the simulation. */
    private void step ()
    {
        // a car arrives approximately every four minutes
        int chance = randGen.nextInt(CarWashApplication.CHANCE_INT);
        if (chance == 0)
        {
            waitingLine.enqueue(new Car(currentTime));
            numCars++;

            /** For printed output of each step */
            //System.out.println(currentTime);
            //waitingLine.toPrint();
        }

        // process the waiting cars
        if (bay.isEmpty() && !waitingLine.isEmpty())
        {
            bay.startWash();
            Car car = (Car) waitingLine.dequeue();
            waitTimeArray[arrayIndex] = currentTime - (car.arrivalTime());
            arrayIndex++;
        }

        if (!bay.isEmpty())
            bay.keepWashing();

        currentTime++;
    }
}
