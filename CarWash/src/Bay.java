/**
 *  Car Wash Simulation Project:  Bay Class
 * The Car Wash Simulation Project is described in <a href="http://max.cs.kzoo.edu/cs210/Labs/Queues/CarWashProgram.html">CarWash Project Description</a>.
 * Authors:   Autumn C. Spaulding and Alyce Brady, based on a description by <a href="mailto:trollend@nb.net">Todd Ollendyke</a>.
 * Date:      13 July 2000
 * Modified:  12 October 2000
 * Added Bay class.
 * Modified:  21 April 2013 by Alyce Brady
 * Parameterized durationOfCarWash.
 * @author Andrew Parsons
 * @version 03 May 2016
 */

/**
 *  This class represents a car wash bay in the Car Wash program.  In
 *  particular, it keeps track of when the bay is empty or, if
 *  there is a car being washed, how long it will be until the bay
 *  is empty again.
 *
*/
public class Bay
{
    private int timeToWashACar;
    private int timeLeftTillEmpty;

    /** Construct a Car Wash Bay */
    public Bay (int durationOfCarWash)
    {
        timeToWashACar = durationOfCarWash;
        reset();
    }

    /** Re-initialize the bay for the start of a new run of the simulation. */
    public void reset ()
    {
        // reset bay to be empty

        int timeLeftTillEmpty = 0;
    }

    /** Is the bay empty, or is there a car in it being washed? */
    public boolean isEmpty ()
    {
        return this.timeLeftTillEmpty <= 0;
    }

    /** Start washing a new car.  This function sets the timer to show how
     *  many more minutes it will take to finish washing this new car. 
     */ 
    public void startWash ()
    // pre: isEmpty()
    {
        // Set timer to indicate how many minutes to go.  (If a car wash
        // takes 3 minutes, that means the current minute plus 2 more.)

        timeLeftTillEmpty = timeToWashACar;
    }

    /** This function tells the bay about the passage of time as it washes
     *  a car.
     */
    public void keepWashing ()
    // pre: ! isEmpty()
    // post: bay is one unit of time closer to being empty
    {
        // Check that pre-condition is met to ensure that we don't go
        // into negative numbers!

        if (!this.isEmpty())
        {
            timeLeftTillEmpty--;
            //System.out.println("Until Empty: " + timeLeftTillEmpty);
        }
    }

    public int getTimeToWashACar()
    {
        return timeToWashACar;
    }

}  // end Bay class
