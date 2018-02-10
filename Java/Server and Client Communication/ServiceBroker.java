/* Eric Neiman
 * CMSC 355 Individual Assignment 02
 * Server.java
 * *****************************************
 * Takes client input and sends it to the Service1.jar and then returns a synonym to the client.
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class ServiceBroker { 
	public static void main(String[] args) throws Exception {
		int serverPortNumber = 5134; // server port number
	    String str; // string for passing input and outputs
	    ServerSocket servSocket = new ServerSocket(serverPortNumber); // creates server socket 
	    System.out.println("Waiting for a connection on " + serverPortNumber); // default message
	    Socket fromClientSocket = servSocket.accept(); // server socket accepts connection to client socket
	    PrintWriter pw = new PrintWriter(fromClientSocket.getOutputStream(), true); // creates PrintWriter to output to client
	    BufferedReader br = new BufferedReader(new InputStreamReader(fromClientSocket.getInputStream())); // creates BufferedReader to take input from client
	    while ((str = br.readLine()) != null) {
	    	System.out.println("Client input: " + str); // prints client input
	    	try {
				String toService1 = "java -jar Service1.jar " + str; // creates string to call jar with argument given
				Process p = Runtime.getRuntime().exec(toService1);
				BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream())); // buffered reader for Service1.jar's output
				String line = in.readLine(); // sets line to Service1.jar's output
				pw.println(line); // prints the output
				System.out.println("Server output: " + line); // prints server output
				while ((line = in.readLine()) != null) { // loops through Service1.jar's output and trims it
					line = in.readLine();
					line = line.trim(); // trims the output
					pw.println(line); 
				}
			} catch (Exception error) { // Catches any Errors
				pw.println("IOException: " + error); // prints error message
				error.printStackTrace();
			}
	    }
	    pw.close(); // closes PrintWriter
	    br.close(); // closes BufferedReader
	    fromClientSocket.close(); // closes client socket
		servSocket.close(); // closes server socket
	}	
}