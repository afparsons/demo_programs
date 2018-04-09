import java.util.LinkedList;
import java.util.NoSuchElementException;

/**
 * Created by Andrew Parsons on 28 April 2016.
 * @author Andrew Parsons
 * @version 03 May 2016
 */
public class LLQueue<T> implements KQueue {

    private LinkedList<T> queue;

    /**
     * Constructor. Initializes empty queue.
     */
    LLQueue() {

        queue = new LinkedList<>();
    }

    /**
     * Checks if queue is empty.
     * @return boolean. true if empty.
     */
    public boolean isEmpty() {

        if (queue.size() == 0)
            return true;
        return false;
    }

    /*public void enqueue(T item)
    {
        queue.add(item);
    }*/

    @Override
    public void enqueue(Object item) {

        queue.add((T) item);
    }

    public T dequeue() {

        try {
            return (T) queue.removeFirst();
        } catch (NoSuchElementException e) {
            return null;
        }
    }

    public T peekFront() {

        return queue.peekFirst();
    }

    public String toString() {

        String returnString = "";//("Queue: " + queue);
        T[] queueElements = (T[]) queue.toArray();

        if (queue.size() > 0)
            for (int i = 0; i < queue.size(); i++)
                returnString += ("[" + i + "] " + queueElements[i].toString());
        else
            returnString = "Empty";

        return returnString;
    }

    public void toPrint() {

        System.out.println("----------------------------");
        System.out.println("Number of queued elements: " + queue.size());
        Object[] queueElements = queue.toArray();

        for (int i = 0; i < queue.size(); i++)
            System.out.println("[" + i + "] " + queueElements[i].toString());
        System.out.println("----------------------------");
        System.out.println("");
    }
}


