
float y,u,x0,x1,x2=0;        
int n, offset=0;

void plot_both(void);

void setup() {Serial.begin(115200);}

void loop() 

{
  
   u = (float)analogRead(0)*5/1023.5;
   
   x0 = u;
    

  // y[n] =  1/T (x[n] -  x[n-1])
    
   y =  0.3*x0 - 0.3*x1;

   
   x1 = x0;
  
    
    
    plot_both();
    
  
} 
  
 void plot_both(void)
{
  offset=3;
  Serial.print(u + offset);
  Serial.print(",");
  Serial.println(y);
  //delay(10);

} 
  


