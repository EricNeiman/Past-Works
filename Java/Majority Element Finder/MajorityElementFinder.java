/* Eric Neiman
 * Majority Element Finder in Array O(N) efficiency
 */
import java.util.Scanner;

public class NeimanEric { // start of NeimanEric class
	
	public static void main(String[] args) { // main method
		Scanner userIn = new Scanner(System.in); // creates a scanner that will take in user input
		int arraySize = userIn.nextInt(); // takes the first input from the user that it is
		int[] numArray = new int[arraySize]; // creates an integer array to store the user input
		for(int i = 0; i < arraySize; i++) {numArray[i] = userIn.nextInt();} // fills the array with user inputs.
		userIn.close(); // closes the user input scanner
		System.out.println(algorithmV(numArray, arraySize)); // calls algorithmV method to find the majority element
	} // end of main method
	
	public static int algorithmV(int[] array, int size) { // finds the majority element in the array and returns it
		if (size == 1) {return array[0];} // if there is one element it is the majority element
		
		int majEle = array[0]; // Select first element as candidate M.E.
		int countMaj = 1; // set counter to 1
		
		for (int i = 1; i < size; i++) { // starts the loop at the second element in the array

			if (majEle == -1){ // candidate M.E. is -1
				majEle = array[i]; // set candidate M.E.
				countMaj = 1; // reset counter
			}
			else if (majEle == array[i]) { // another copy of candidate M.E.
				countMaj++; // -increase counter
			} 
			else if (majEle != array[i]) { // some other element X
				countMaj--; // -decrease counter
				if (countMaj == 0) { // if after deletion counter is 0
					majEle = -1; // -1 is the place holder for no candidate majority element
				}
			} 
			
		}
		return majEle; // returns majority element
	} // end of algorithmV method
	
} // end of NeimanEric class
