// Class: NQueens
//
// Author: Your Name Here
//
// License Information:
//   This class is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation.
//
//   This class is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.

import edu.kzoo.grid.BoundedGrid;
import edu.kzoo.grid.Grid;
import edu.kzoo.grid.Location;
import edu.kzoo.grid.display.GridDisplay;

/**
 *  Environment-Based Applications:<br>
 *
 *    The NQueens class implements the N Queens problem.
 *
 *  @author Andrew Parsons (based on a template provided by Alyce Brady)
 *  @version 19 May 2016
 **/

public class NQueens
{
    // Instance Variables: Encapsulated data for EACH NQueens problem
    private Grid board;
    private GridDisplay display;

  // constructor

    /** Constructs an object that solves the N Queens Problem.
     *    @param n the number of queens to be placed on an
     *              <code>n</code> x <code>n</code> board
     *    @param d an object that knows how to display an 
     *              <code>n</code> x <code>n</code> board and
     *              the queens on it
     **/
    public NQueens(int n, GridDisplay d)
    {
        board = new BoundedGrid(n, n);
        display = d;
        display.setGrid(board);
        display.showGrid();
    }

  // methods

    /** Returns the number of queens to be placed on the board. **/
    public int numQueens()
    {
        return board.numCols();
    }

    /** Solves (or attempts to solve) the N Queens Problem. **/
    public boolean solve()
    {
        placeQueen(0);
        if (board.allObjects().length == board.numCols())
        {
            return true;
        } else {
            System.out.println("Cannot solve for this N.");
            return false;
        }
    }

    /** Attempts to place the <code>q</code>th queen on the board.
     *  (Precondition: <code>0 <= q < numQueens()</code>)
     *    @param q index of next queen to place
     **/
    private boolean placeQueen(int q)
    {
        if (q >= board.numCols())
            return true;
        for (int colCounter = 0; colCounter < board.numCols(); colCounter++)
        {
            Location loc = new Location(q,colCounter);

            if (locationIsOK(loc))
            {
                addQueen(loc);
                if (placeQueen(q+1))
                {
                    return true;
                }
            }
            removeQueen(loc);
        }
        return false;
    }

    /** Determines whether a queen can be placed at the specified
     *  location.
     *    @param loc  the location to test
     **/
    private boolean locationIsOK(Location loc)
    {
        int locRow = loc.row();
        int locCol = loc.col();

        // --- check that no queens are in column --- //
        for (int traverseRow = 0; traverseRow < board.numCols(); traverseRow++)
        {
            if (! board.isEmpty(new Location (traverseRow,locCol)))
            {
                return false;
            }
        }

        // --- check that no queens are in backwards diagonal --- //
        if (loc.row() != 0) // seems hacky
        {
            Location checkBack = new Location(locRow - 1, locCol - 1); // the location we are checking

            while (checkBack.row() >= 0 && checkBack.col() >= 0 ) {

                if (board.isEmpty(checkBack)) {
                    int cbRow = checkBack.row();
                    int cbCol = checkBack.col();
                    checkBack = new Location(cbRow - 1, cbCol - 1);
                } else {
                    return false;
                }
            }
        }

        // --- check that no queens are in forwards diagonal --- //
        if (locRow != 0 && locCol != board.numCols() -1) //seems hacky
        {
            Location checkForward = new Location(locRow - 1, locCol + 1); // the location we are checking
            int colCount = board.numCols()-1; // stop condition

            while (checkForward.row() >= 0 && checkForward.col() <= colCount) {

                if (board.isEmpty(checkForward)) {
                    int cbRow = checkForward.row();
                    int cbCol = checkForward.col();
                    checkForward = new Location(cbRow - 1, cbCol + 1);
                } else {
                    return false;
                }
            }
        }

        return true;
    }

    /** Adds a queen to the specified location.
     *    @param loc  the location where the queen should be placed
     **/
    private void addQueen(Location loc)
    {
        new Queen(board, loc);
        display.showGrid();
    }

    /** Removes a queen from the specified location.
     *    @param loc  the location where the queen should be removed
     **/
    private void removeQueen(Location loc)
    {
        board.remove(loc);
    }

}
