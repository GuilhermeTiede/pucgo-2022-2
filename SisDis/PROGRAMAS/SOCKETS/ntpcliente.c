/* Comentar e explicar o código. Leia o livro texto e as seguintes RFC:958, 1305 e 5905 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define NTP_TIMESTAMP_DELTA 2208988800ull

#define LI(packet)   (uint8_t) ((packet.li_vn_mode & 0xC0) >> 6) // (li   & 11 000 000) >> 6
#define VN(packet)   (uint8_t) ((packet.li_vn_mode & 0x38) >> 3) // (vn   & 00 111 000) >> 3
#define MODE(packet) (uint8_t) ((packet.li_vn_mode & 0x07) >> 0) // (mode & 00 000 111) >> 0



void error( char* msg )
{
    perror( msg ); //Exibir a mensagem de erro

    exit( 0 );//Sai do processo 
}



int main( int argc, char* argv[ ] )
{
  int sockfd, n;// Sockfd -> Descritor de arquivo sckt || n -> Retorna o que foi gravado e lido no socket

  int portno = 123; //número da porta UDP e NTP

  //char* host_name = "us.pool.ntp.org"; //Nome do server NTP USA
  char* host_name = "br.pool.ntp.org"; // Nome do server NTP BR


  

  typedef struct
  {

    uint8_t li_vn_mode; // 8 bits, li(2bits) - Indica o salto, vn(3bits)Numero da versao do Protocolo, mode(3bits) Client    
                             
                             
                            

    uint8_t stratum; // 8-bits Nível do relógio da máquina         
    uint8_t poll;// 8-Bits Intervalo máximo entre mensagens        
    uint8_t precision;// 8-Bits Precisão do relógio da Máquina      

    uint32_t rootDelay;// 32 Bits -> Delay de ido e volta
    uint32_t rootDispersion;//32 Bits Erro máximo com o relógio principal
    uint32_t refId;//32Bits -> Identificado do relógio de referência

    uint32_t refTm_s;//Instante de tempo que referencia os Segundos (32bits)
    uint32_t refTm_f;//Instante de tempo que referencia uma fração de segundos(32Bits)

    uint32_t origTm_s;//Origina instante de tempo Segundos(32Bits)
    uint32_t origTm_f;//Origina instante de tempo fração de segundos(32Bits)

    uint32_t rxTm_s;//Recebe instante de tempo Segundos(32Bits)
    uint32_t rxTm_f;//Recebe instante de tempo fração de segundos(32Bits)

    uint32_t txTm_s;//Transmite o instante Segundos (Campo que o Cliente mais se preocupa)32Bits
    uint32_t txTm_f;//Transmite o instante de tempo fração de segundo.

  } ntp_packet; // 384 Bits --> 48 Bytes.        

  
  //Criar e zerar o pacote -> 48 Bytes
  ntp_packet packet = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };



  memset( &packet, 0, sizeof( ntp_packet ) );


  //Setar o primeiro bit dos bytes para 00, 011, 001 para li = 0, vn = 3 e mode = 3. O resto será setado como 0
  *( ( char * ) &packet + 0 ) = 0x1b; 

  //Cria o Socket UDP, converte o Host-Name para Endereço IP, seta o número da porta, conecta no servidor, mandar o pacote
  //e lê o pacote que foi retornado.


  struct sockaddr_in serv_addr;//Estrutura de dados do endereço do servidor
  struct hostent *server;//Estrutura de dados do servidor

 
 sockfd = socket( AF_INET, SOCK_DGRAM, 0); // Cria o socket UDP
//   sockfd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); 

  if ( sockfd < 0 )
    error( "ERROR opening socket" );

  server = gethostbyname( host_name );//Converte o URL para IP

  if ( server == NULL )
    error( "ERROR, no such host" );


//Zera a estrutura de dados do servidor.
  bzero( ( char* ) &serv_addr, sizeof( serv_addr ) );

  serv_addr.sin_family = AF_INET;

 //Copia o IP do servidor para a estrutura de dados do servidor

  bcopy( ( char* )server->h_addr, ( char* ) &serv_addr.sin_addr.s_addr, server->h_length );

 //Converte o número Inteiro da porta para o estilo "Big-Endian" e salva ele na estrutura de dados do servidor

  serv_addr.sin_port = htons( portno );

//chama o servidor usandoo o IP e a porta como paramêtro.

  if ( connect( sockfd, ( struct sockaddr * ) &serv_addr, sizeof( serv_addr) ) < 0 )
    error( "ERROR connecting" );

//Envia o pacote NTP se necessário, se n<0 ele retorna falha

  n = write( sockfd, ( char* ) &packet, sizeof( ntp_packet ) );

  
if ( n < 0 ) error( "ERROR writing to socket" );

 
//Espera e ver se recebe o pacote de volta, se n<0 ele retorna falha.

 n = read( sockfd, ( char* ) &packet, sizeof( ntp_packet ) );

  if ( n < 0 ) error( "ERROR reading from socket" );

 //packet.txTm_s e packet.txTm_f armazenam o instante de tempo em segundos e fração de segundos quando o pacote saiu do server NTP,
 //considereando os segundos dedesde 1970 e o nthol() converte a ordem de bit e byte da rede para o "endianness" do host

  packet.txTm_s = ntohl( packet.txTm_s ); 



  packet.txTm_f = ntohl( packet.txTm_f ); 

//Extrai os 32bits a onde estao os segundos armazenados do timestamp desde quando o pacote saiu do server e subtrai 70 anos em segundos
//desde 1970

  time_t txTm = ( time_t ) ( packet.txTm_s - NTP_TIMESTAMP_DELTA );

//Imprimir a hora que recebemos do o pacote do servdior usando como base o horário local e a conversão de tempo UTC.

  printf( "%s", ctime( ( const time_t* ) &txTm ) );


  return 0;
}