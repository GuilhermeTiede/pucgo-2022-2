/**
 * MessageQueueImpl.java
 *
 * This is the implementation of the interface for the RMI-based message passing
 * solution to the bounded buffer problem.
 *
 * @author Greg Gagne, Peter Galvin, Avi Silberschatz
 * @version 1.0 - July 15, 1999
 * Copyright 2000 by Greg Gagne, Peter Galvin, Avi Silberschatz
 * Applied Operating Systems Concepts - John Wiley and Sons, Inc.
 */
 
import java.util.*;
import java.rmi.*;
 
public class MessageQueueImpl extends java.rmi.server.UnicastRemoteObject implements MessageQueue 
{
   public MessageQueueImpl() throws RemoteException {
	  queue = new Vector();
   }   
   
   // This implements a non-blocking send
   public synchronized void send(Object item) throws RemoteException {
	  queue.addElement(item);
	  
	  System.out.println("Producer entered " + item + " size = " + queue.size());
   }   
   
   // This implements a non-blocking receive
   public synchronized Object receive() throws RemoteException {
	  Object item;
	  
	  if (queue.size() == 0)
		 return null;
	  else {
		 item = queue.firstElement();        
		 queue.removeElementAt(0);
	  
  	System.out.println("Consumer removed " + item + " size = " + queue.size());
		 
		 return item;
	  }
   }   

   public static void main(String args[]) {
	System.setSecurityManager(new RMISecurityManager());
	
	try {
		MessageQueue server = new MessageQueueImpl();
				Naming.rebind("//127.0.0.1/MessageServer", server);
		System.out.println("Server Bound");
	}
	catch(Exception e) {
		System.err.println(e);
	}
	
   }   
   
   private Vector queue;
}