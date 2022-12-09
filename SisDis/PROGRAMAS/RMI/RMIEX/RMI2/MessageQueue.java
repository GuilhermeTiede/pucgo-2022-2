/**
 * MessageQueue.java
 *
 * This is the interface for the RMI-based message passing
 * solution to the bounded buffer problem.
 *
 * @author Greg Gagne, Peter Galvin, Avi Silberschatz
 * @version 1.0 - July 15, 1999
 * Copyright 2000 by Greg Gagne, Peter Galvin, Avi Silberschatz
 * Applied Operating Systems Concepts - John Wiley and Sons, Inc.
 */

import java.util.*;
import java.rmi.*;
 
public interface MessageQueue extends java.rmi.Remote 
{
   /*
	* This implements a non-blocking send
	*/
   public void send(Object item) throws java.rmi.RemoteException;   
   
   /*
	* This implements a non-blocking receive
	*/
	
   public Object receive() throws java.rmi.RemoteException;   
}