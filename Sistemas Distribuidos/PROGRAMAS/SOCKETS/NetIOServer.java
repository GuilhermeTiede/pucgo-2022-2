//Exemplo de Servidor para o Cliente NETIO http://netio.davideickhoff.de

import java.net.Socket;
import java.net.ServerSocket;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.IOException;

public class NetIOServer {
    private int serverPort = 0; //parametros sao atribuidos no main
    private ServerSocket serverSock = null;

    public NetIOServer(int serverPort) {
        this.serverPort = serverPort;

        try {
            serverSock = new ServerSocket(serverPort);
        }
        catch (IOException e){
            e.printStackTrace(System.err);
        }
    }
    
  
    public void handleConnection(InputStream sockInput, OutputStream sockOutput) {
        while(true) {
            byte[] buf=new byte[1024]; //limite do buffer de mensagens
            int bytes_read = 0;
            try {
               //aguarda o envio de msg ou a finalizacao da conexao

                bytes_read = sockInput.read(buf, 0, buf.length);

                // se a conexao e fechada, sockInput.read() retornara -1.
                if(bytes_read < 0) {
                    System.err.println("Falha na Conexao,  Finalizando o socket.");
                    return;
                }
                System.err.println("Tamanho da msg recebida: "+bytes_read
                                   +" bytes, Conteúdo:" +(new String(buf, 0, bytes_read)));

                //devolve a mesma string ao cliente 
			sockOutput.write(buf, 0, bytes_read);

                
                sockOutput.flush(); //chamada opcional, evita que os dados fiquem presos em buffers
            }
            catch (Exception e){
                System.err.println("Falha na leitura do socket:"+e);
                e.printStackTrace(System.err);
                return;
            }
        }

    }

    public void waitForConnections() {
        Socket sock = null;
        InputStream sockInput = null;
        OutputStream sockOutput = null;
        while (true) {
            try {

                sock = serverSock.accept();

                System.err.println("Nova Conexão Recebida");

               //Atencao: é um servidor iterativo!

                sockInput = sock.getInputStream();
                sockOutput = sock.getOutputStream();
            }
            catch (IOException e){
                e.printStackTrace(System.err);
            }


            handleConnection(sockInput, sockOutput);

            // Finaliza o socket, a conexao do cliente.
            try {
                System.err.println("Cliente Finalizado.");
                sock.close();
            }
            catch (Exception e){
                System.err.println("Erro na finalizacao do Cliente");
                e.printStackTrace(System.err);
            }

            System.err.println("Aguardando Novo Cliente...");
        }
    }

    public static void main(String argv[]) {
        int port = 1234;
        NetIOServer server = new NetIOServer(port);
        server.waitForConnections();
    }
}