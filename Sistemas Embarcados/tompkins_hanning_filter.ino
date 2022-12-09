
extern int _32_senoide_32hz_[32];
int offset = 0;


void setup() {Serial.begin(115200);}

void loop() {
  
  
 /* 
  uint8_t i;
  for(i=0;i<31;i++){
                     Serial.print(_32_senoide_32hz_[i]+offset);
                     Serial.print(","); 
                     //hanning do livro de tompkins
                     Serial.println(_32_senoide_32hz_[i]/4 +_32_senoide_32hz_[i-1]/2 +_32_senoide_32hz_[i-2]/4);  
                     // delay(100);
  					}
  */
  
int xnt, xm1, xm2, ynt;
xm2 = 0;
xm1 = 0;

uint8_t i;
  for(i=0;i<31;i++){

				xnt = _32_senoide_32hz_[i];
    
				ynt = (xnt + (xm1<<2) + xm2)>>4;
                
                //ynt = (xnt + 2*xm1 + xm2)/4;            
    
				Serial.print(xnt);
				Serial.print(",");
				Serial.println(ynt);    
				xm2 = xm1;
				xm1 = xnt;
    
                //delay(100);
					}
  
  
  
  
}


/*senoide gerada pelo matlab
%32 mostras entre 0 e 2pi com amplitude de 5000 mv ou 10000mv pico a pico

clear all;
close all;
clc;

x= 0 : 0.2 : 2*pi;
y = 5000* sin (x);
arduino = round (y);

plot (x,y);

*/
int _32_senoide_32hz_[32]=
{
0,
993,
1947,
2823,
3587,
4207,
4660,
4927,
4998,
4869,
4546,
4042,
3377,
2578,
1675,
706,
-292,
-1278,
-2213,
-3059,
-3784,
-4358,
-4758,
-4968,
-4981,
-4795,
-4417,
-3864,
-3156,
-2323,
-1397,
-415,
};		
  
  

/**************************************************************
p. 103
O filtro Hanning calcula uma média móvel ponderada, uma vez que os dados centrais
(elementos centrais da equação) tem o dobro do peso dos outros dois:

y(nT) = 1/4 [x(nT) + 2x(nT – T) + x(nT – 2T)] (5.6)


Equação de diferenças

y(nT) = (x(nT) + 2*x(nT - T) + x(nT - 2T))/4

Em linguagem C:
ynt = (xnt + 2*xm1 + xm2)/4;

main()
{
int i, xnt, xm1, xm2, ynt, idb[256];
xm2 = 0;
xm1 = 0;
for(i = 0; i <= 255; i++)
{
xnt = idb[i];
ynt = (xnt + 2*xm1 + xm2)/4;
idb[i] = ynt;
xm2 = xm1;
xm1 = xnt;
}
}

A equação de diferenças computada usando operadores de deslocamento da linguagem C 
para fazer as multiplicações de forma mais eficiente. 
A expressão << 1 é um deslocamento binário para a esquerda por uma posição de bit
correspondendo à multiplicação por um fator de dois, e a expressão 
>> 2 é um deslocamento binário à direita de posições de dois bits que representam a divisão por quatro.

as variáveis ​​de dados de entrada são deslocadas através dos blocos de atraso como no
programa anterior. 

Para a próxima entrada, o ponto de dados que era um ponto no passado
x (nT - T) (chamado xm1 no programa) move dois pontos no passado e se torna
x (nT - 2T) (ou xm2). A entrada mais recente x (nT) (chamada xnt) move um ponto
de volta no tempo, substituindo x (nT - T) (ou xm1).

Assim, o novo programa implmenta a mesma equação ynt = (xnt + xm1<<1 + xm2)>>2;



main()
{
int i, xnt, xm1, xm2, ynt;
xm2 = 0;
xm1 = 0;

for( ; ; )
{

xnt = adget(A/D); análogo ao readanalog do arduino
ynt = (xnt + xm1<<1 + xm2)>>2;
daput(ynt, DA);
xm2 = xm1;
xm1 = xnt;
}
}




*/

