/**
 * Consumer.java
 *
 * This is the consumer thread for the bounded buffer problem.
 * Communication is achieved using RMI.
 *
 * @author Greg Gagne, Peter Galvin, Avi Silberschatz
 * @version 1.0 - July 15, 1999
 * Copyright 2000 by Greg Gagne, Peter Galvin, Avi Silberschatz
 * Applied Operating Systems Concepts - John Wiley and Sons, Inc.
 */

import java.util.*;

class Consumer extends Thread
{
   public Consumer(MessageQueue m)
   {
	  mbox = m;
   }   
   
   public void run()
   {
   Date message;
   
	 while (true)
	  {
	Factory.napping();
		 
		 // consume an item from the buffer
	try {         
		 message = (Date)mbox.receive();
		 
		 if (message != null)
	  // Consume the item
		;
	}
	catch (Exception e) {
		System.err.println(e);
	}
	  }
   }   
   
   private  MessageQueue mbox;
}