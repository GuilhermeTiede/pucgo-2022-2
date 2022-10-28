/**
 * Producer.java
 *
 * This is the producer thread for the bounded buffer problem.
 * Communication is achieved using RMI.
 *
 * @author Greg Gagne, Peter Galvin, Avi Silberschatz
 * @version 1.0 - July 15, 1999
 * Copyright 2000 by Greg Gagne, Peter Galvin, Avi Silberschatz
 * Applied Operating Systems Concepts - John Wiley and Sons, Inc.
 */

import java.util.*;

class Producer extends Thread
{
   public Producer(MessageQueue m)
   {
	  mbox = m;
   }                 
   
   public void run()
   {
   Date message;
	 
	  while (true)
	  {
	Factory.napping();
   
		 // produce an item & enter it into the buffer
		 message = new Date();      

	try {           
		 mbox.send(message);
	}
	catch (Exception e) {
		System.err.println(e);
	}
	  }
   }   
   
   private  MessageQueue mbox;
}