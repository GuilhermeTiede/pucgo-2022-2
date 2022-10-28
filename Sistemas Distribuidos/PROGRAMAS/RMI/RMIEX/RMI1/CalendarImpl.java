import java.util.Date;
import java.rmi.*;
import java.rmi.registry.*;
import java.rmi.server.*;


//-----------------------------------------
// Classe: CalendarImpl
//         Realiza a interface iCalendar 
//-----------------------------------------
public class CalendarImpl extends UnicastRemoteObject implements iCalendar // a iCalendar disponibiliza os metodos
{

//----- class constructor
  public CalendarImpl ()
  throws RemoteException //obrigatorio
	{
	  System.out.println ("Server object was created.") ;
	}


//----- getDate implementation
  public Date getDate ()    // metodo que vai ser dicponibilizado pelo RMI -> nova data
  throws RemoteException
	{
	  System.out.println ("Calendar server accessed.") ;
	  return new Date () ;
	}


//----- main class code
  public static void main (String args [])
	{
	 System.setSecurityManager(new RMISecurityManager());  
      CalendarImpl cal ;
	  
	  try
	{
	  //LocateRegistry.createRegistry (1099) ; 
       cal = new CalendarImpl () ;
	  Naming.bind ("rmi://127.0.0.1/CalendarImpl", cal) ; // referencia aa instancia call
	  System.out.println  ("Server object is ready for RMIs") ;
	}

	  catch (Exception e)
	{
	  e.printStackTrace () ;
	}
	}
}