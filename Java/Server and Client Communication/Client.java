/* Eric Neiman
 * CMSC 355 Individual Assignment 02
 * Client.java
 * *****************************************
 * Takes user input and sends it to the server and then returns a synonym.
 */

import java.io.*;
import java.util.Scanner;
import java.net.InetAddress;
import java.net.Socket;

public class Client {
	public static void main(String[] args) throws Exception { 
		Socket socket1; // socket for connection
	    int portNumber = 5134; // server port number
	    Scanner userIn = new Scanner(System.in); // creates scanner
	    socket1 = new Socket(InetAddress.getLocalHost(), portNumber); // connects to server
	    BufferedReader br = new BufferedReader(new InputStreamReader(socket1.getInputStream())); // input from the server
	    PrintWriter pw = new PrintWriter(socket1.getOutputStream(), true); // output to server
	    System.out.print("Enter an English word or phrase to get a synonym from the server (port number: " + portNumber + "): ");
	    String str = userIn.nextLine(); // user input
	    pw.println(str); // prints to server
	    str = br.readLine(); // reads from server
	    System.out.println(str); // prints server output
	    br.close(); // closes BufferedReader
	    pw.close(); // closes PrintWriter
	    socket1.close(); // closes socket
	    userIn.close(); // closes scanner
	}
}