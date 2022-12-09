import java.util.Date;
import java.rmi.*;

public class CalendarUser
{
  public static void main (String args[])
	{
	  long t1=0, t2=0 ;
	  Date date ;
	  iCalendar remoteCal ;
	  
	  try
	{
	  remoteCal = (iCalendar)Naming.lookup //acessa atraves do servidor de nomes o metodo lookup
	    ("rmi://127.0.0.1/CalendarImpl") ; 
	  t1 = remoteCal.getDate().getTime() ; //retorna data/hora
	  t2 = remoteCal.getDate().getTime() ;
	}

	  catch (Exception e)
	{
	  e.printStackTrace () ;
	}

	  System.out.println ("This RMI call took " + (t2 -t1) + " milliseconds") ;
	}

}