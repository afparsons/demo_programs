/**
 * Andrew Parsons on 11/12/16.
 * This short bit of code serves as a simulation of the Monty Hall Problem.
 * https://en.wikipedia.org/wiki/Monty_Hall_problem
 */

import java.util.Random;
import java.util.Scanner;
public class MontyHall {

    public static void main(String[] args) {

        // counters
        double stayWinCount = 0;
        double switchWinCount = 0;

        // scanner takes user input for number of doors and number of simulations
        Scanner input = new Scanner(System.in);
        System.out.println("Enter number of doors: ");
        int arraySize = input.nextInt();
        System.out.println("Enter number of repetitions: ");
        double repetitions = input.nextInt();

        // random is used to randomly choose doors
        Random randomGenerator = new Random();

        // loop simulations
        for (int i = 0; i < repetitions; i++) {

            // doors are stored in an array the length of the number of doors
            int[] doors = new int[arraySize];

            // set all doors to have a goat
            for (int door : doors) {
                door = 0;
            }

            // place a prize behind exactly one door
            doors[randomGenerator.nextInt(arraySize)] = 1;

            // contestant chooses one door
            int chosen = randomGenerator.nextInt(arraySize);

            // host reveals one door different from the contestant's choice and the winning door
            int revealed;
            do {
                revealed = randomGenerator.nextInt(arraySize);
            }
            while (revealed == chosen || doors[revealed] == 1);

            // if the contestant's chosen door is the same as the winning door, increment the "stay" counter
            if (doors[chosen] == 1) {
                stayWinCount = stayWinCount + 1;
            }

            // if the contestant were to switch and win, increment the "switch" counter
            int switchChoice;
            do {
                switchChoice = randomGenerator.nextInt(arraySize);
            } while ((switchChoice == chosen) || (switchChoice == revealed));

            if (doors[switchChoice] == 1) {
            switchWinCount = switchWinCount + 1;
            }
        }

        // print results
        double stayProportion = (stayWinCount/repetitions);
        double switchProportion = (switchWinCount/repetitions);
        System.out.println("Stay wins: " + stayWinCount + " | Proportion: " + stayProportion);
        System.out.println("Switch wins: " + switchWinCount + " | Proportion: " + switchProportion);
    }
}