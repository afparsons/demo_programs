/**
 * Car Wash Simulation Project:  CarWashApplication Class
 * The Car Wash Simulation Project is described in
 * <a href="http://max.cs.kzoo.edu/cs210/Labs/Queues/CarWashProgram.html">Car
 * Wash Project Description</a>.
 * Authors:   Autumn C. Spaulding and Alyce Brady, based on a description by <a href="mailto:trollend@nb.net">Todd Ollendyke</a>.
 * Date:      13 July 2000
 * Modified:  12 October 2000: Added Bay class and separated simulation behavior from main into the CarWashSimulation class.
 * Modified:  29 October 2002: Separated class templates into separate files.
 * @author Andrew Parsons
 * @version 03 May 2016
*/

/**
 *  This is the main class for the Car Wash program.
 */
public class CarWashApplication
{
    /** Bay wash cycle duration, in minutes */
    static final int BAY_TIME = 3;

    /** Car wash running time, in minutes (09:00 - 19:00) */
    static final int DAY_LENGTH = 600;

    /** Frequency of car arrival, where frequency is determined by ( 1 / CHANCE_INT ) | CANNOT BE 0 ! */
    static final int CHANCE_INT = 4;

    /**
     *  The main function constructs a car wash simulation and asks it to run.
     */
    public static void main(String args[])
    {
        // create simulation
        CarWashSimulation sim = new CarWashSimulation();

        // --- OUTPUT --- //

        System.out.println("Squeaky Clean Car Wash -- Open 09:00 through 19:00 -- 1 bay / " + BAY_TIME + " minutes");
        System.out.println("################################################################################");
        System.out.println();
        double weeklyAverage = 0;
        for (int i = 0; i < 7; i++)
        {
          if (i == 0) { System.out.println("MONDAY"); weeklyAverage += sim.run(DAY_LENGTH); }
          if (i == 1) { System.out.println("TUESDAY"); weeklyAverage += sim.run(DAY_LENGTH); }
          if (i == 2) { System.out.println("WEDNESDAY"); weeklyAverage += sim.run(DAY_LENGTH); }
          if (i == 3) { System.out.println("THURSDAY"); weeklyAverage += sim.run(DAY_LENGTH); }
          if (i == 4) { System.out.println("FRIDAY"); weeklyAverage += sim.run(DAY_LENGTH); }
          if (i == 5) { System.out.println("SATURDAY"); weeklyAverage += sim.run(DAY_LENGTH); }
          if (i == 6) { System.out.println("SUNDAY"); weeklyAverage += sim.run(DAY_LENGTH); }
        }
        weeklyAverage = weeklyAverage / 7;
        weeklyAverage = Math.round(weeklyAverage * 100);
        weeklyAverage = weeklyAverage / 100;
        System.out.println("################################################################################");
        System.out.println("Squeaky Clean Car Wash: Average Waiting Time only " + weeklyAverage + " minutes w/ one " + BAY_TIME + " min bay!");
    }
}
