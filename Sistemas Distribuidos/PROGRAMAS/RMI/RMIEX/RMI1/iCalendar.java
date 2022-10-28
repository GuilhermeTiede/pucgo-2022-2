import java.rmi.*;

public interface iCalendar extends Remote //remote para habilitar o RMI 
{
  java.util.Date getDate() // retorna data
  throws RemoteException ; // todos os metodos teem que retornar esta excessao  
}