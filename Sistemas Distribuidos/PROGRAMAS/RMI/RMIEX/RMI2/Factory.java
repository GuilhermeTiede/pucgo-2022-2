/**
 * Factory.java
 *
 * This creates the buffer and the producer and consumer threads.
 * It then gets a reference to a remote mailbox object
 * and passes it to separate prodcuer and consumer threads.
 *
 * @author Greg Gagne, Peter Galvin, Avi Silberschatz
 * @version 1.0 - July 15, 1999
 * Copyright 2000 by Greg Gagne, Peter Galvin, Avi Silberschatz
 * Applied Operating Systems Concepts - John Wiley and Sons, Inc.
 */

import java.util.*;
import java.rmi.*;
 
public class Factory
{  
   public Factory()
   {
	// remote object
	MessageQueue mailBox;

	System.setSecurityManager(new RMISecurityManager());

	try {
				mailBox = (MessageQueue)Naming.lookup("rmi://127.0.0.1/MessageServer");
	  
	  		// now create the producer and consumer threads
	  		Producer producerThread = new Producer(mailBox);
	  		Consumer consumerThread = new Consumer(mailBox);
	  
	  		producerThread.start();
	  		consumerThread.start();               
	}
	catch (Exception e) {
		System.err.println(e);
	}
   }   

   // producer and consumer will call this to nap
   public static void napping() {
	 int sleepTime = (int) (NAP_TIME * Math.random() );
	 try { Thread.sleep(sleepTime*1000); }
	 catch(InterruptedException e) { }
   }   


   public static void main(String args[])
   {
	  Factory client = new Factory();
   }   
   
   private static final int NAP_TIME = 5;
}