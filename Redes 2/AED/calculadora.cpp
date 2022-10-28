#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

struct subRede
{
    //SubRede
    int* IpBinSub;
    int* IpBinSub = new int [32];
    int *IpDecimalSub = new int[4];

    //Mascara da Rede
    int* IpMascaraBin = new int [32];
    int * IpMascaraDecimal = new int[4];

    //BroadCast
    int* IpBinBroad = new int [32];
    int* IpDecimalBroad = new int[4];

    //Primeiro Host
    int* IpBinPrimeiroValido = new int [32];
    int * IpDecimalPrimeiroValido = new int[4];

    //Ultimo Host
    int* IpBinUltimoValido = new int [32];
    int * IpDecimalUltimoValido = new int[4];

    //Quantidade de mascara da sub rede
    long long maquinaNaSubRede = 0;

};

int* transformaBinario(int num);
bool interarIpBinario(int* ip, int inicio, int fim);

//Validar IP
int bitsRedeClasse(int *ip)
{
    if(ip[0] == 0)
    {
        return 8; //Classe A
    }
    if(ip[0] == 1 && ip[1] == 0)
    {
        return 16; //Classe B
    }
    if(ip[0]== 1 && ip[1] == 1 && ip[2] == 0)
    {
        return 24; // Classe C
    }
    return -1;
}
bool validandoIpv4(int * ip, int cidr)
{
    //Descobrir bits host (Classe)
    int BitsHosthere = bitsRedeClasse(ip);

    if(BitsHosthere == -1)
    {
        string e = "Erro ao validar classe" + cidr;
        cout<<e;
    }
    if(cidr<BitsHosthere)
    {
        string e = "O CIDR precisa ser igual ou maior que a Classe da rede CIDR >" + BitsHosthere;
        cout<<e;
    }
    return true;
}

bool zerosMesmaPosicaoMascaraIpBin(int* mascaraBin, int* ipBin)
{
    int i = 0;
    for(i=0; i<32 &&mascaraBin[1] == 1; i++)
    {}
    for(i; i<32 && ipBin[i] == 0; i++)
    {}
    if(i == 32) return true;
    return false;
}

bool validaIpMascara(int* mascaraBin, int* ipBin)
{
    if(zerosMesmaPosicaoMascaraIpBin(mascaraBin, ipBin)) return true;
    string e = "Nao possui os bits zero no ip como na mascara";
    cout<<e;
    return false;
}

bool validaDec(int x, int y, int z, int t)
{
        if(x>=0 && x<=255)
    {
        if(y>=0 && y<=255)
        {
            if(z>=0 && z<=255)
            {
                if(t>=0 && t<=255)
                {
                    return true;
                }
            }
        }
    }
    string e = "Fora do intervalo 0-255";
    cout<<e;
    return false;
}

void novaMascara(int* oldMascara, int* subMascara, int qtdBits)
{
    int i = 0;

    for(i=0; i<32; i++)
    {
        subMascara[i] = oldMascara[i];
    }

    for(i=0; i<32 && oldMascara[i] == 1; i++){}

    for(i; qtdBits; qtdBits--, i++)
    {
        subMascara[i] = 1;
    }
}

int* retornaVetorzao(int x, int y, int z, int t)
{
    int* vetorzao = new int [32];
    int* vetX;
    int* vetY;
    int* vetZ;
    int* vetT;
    vetX = transformaBinario(x);
    vetY = transformaBinario(y);
    vetZ = transformaBinario(z);
    vetT = transformaBinario(t);
    int indice = 0;
    int i =0;

    for(i=0; i<=7; i++)
    {
        vetorzao[i] = vetX[i];
    }
    indice = i;
    for(i=0, indice; i<=7; indice++,i++)
    {
        vetorzao[indice] = vetY[i];
    }
    for(i=0, indice; i<=7; indice++,i++)
    {
        vetorzao[indice] = vetZ[i];
    }
    for(i=0, indice; i<=7; indice++,i++)
    {
        vetorzao[indice] = vetT[i];
    }

    return vetorzao;

}

int* transformaBinario(int num)
{
    int i = 7;
    int* vet = new int[8];
    while(i >= 0)
    {
         vet[i] = num % 2;
         num = num / 2;
         i--;
    }

    /*for(int x = 0; x < 8; x++)
    {
        cout << vet[x];
    }*/
    return vet;
}

float bitsParaSubRede(int numSub)
{
    return ceil(log2(numSub));
}


//Ip Binario para decimal
int ipDecimal(int* ipBinario, int inicio, int fim)
{
    int i=0, exp=0;
    int decimal = 0;
    for(i=fim; inicio<=i; i-- )
    {
        decimal += pow(2,exp) * ipBinario[i];
        exp++;
    }
    return decimal;
}

void ipDecimalMontador(int* ipBinario, int* decimal)
{
    decimal[0] = ipDecimal(ipBinario, 0, 7);
    decimal[1] = ipDecimal(ipBinario, 8, 15);
    decimal[2] = ipDecimal(ipBinario, 16, 23);
    decimal[3] = ipDecimal(ipBinario, 24, 31);
}

/// Ip Binario para decimal - Fim

int zeroMascara(int* mascara32)
{
    int i = 0;
    for(i=0; i<32 && mascara32[i] == 1; i++){}

    if(i != 32)
    {
        return i;
    }
    return -1; //Nao tem 0 nessa mascara
}

bool numeroDeSubRedesPossiveis(int* mascara, int qntRedes)
{
    int posicao = zeroMascara(mascara);
    int maximo = 32 - posicao;
    if(qntRedes <= 0) throw string("O numero de sub-redes deve ser maior que zero");
    int aux = pow(2,(maximo-2));
    string a = "Acima da quantidade maxima de";
    cout<< a, aux,"subredes";

    if(qntRedes > aux) throw a;
    if(qntRedes > 0 && qntRedes < aux)
    {
        return true;
    }
    return false;
}

bool interarIpBinario(int* ip, int inicio, int fim)
{
    fim--; // corrigindo a posicao final
    int aux = 1;
    int i = 0;

    for(i=fim; inicio<= i; i--)
    {
        aux+= ip[i];
        if(aux == 2)
        {
            aux = 1;
            ip[i] = 0;
            continue;
        }else
        {
            ip[i] = aux;
            aux = 0;
            break;
        }
    }
    if(aux != 0)
    {
        return false;
    }
    return true;

}

bool decrementarIpBinario (int* ip, int inicio, int fim)
{
    fim--;
    int aux = -1;
    int i = 0;

    for(i=fim; inicio<= i; i--)
    {
        aux+= ip[i];
        if(aux == -1)
        {
            ip[i] = 1;
            continue;
        }else
        {
            ip[i] = 0;
            break;
        }
    }

    if(i == inicio-1)
    {
        return false;
    }
    return true;
}

subRede* subRedeMontador (int qtdSubRede,int* mascara, int* ip)
{
    //mascara [4] x.y.z.t , ip[4] x.y.z.t
    int particoesSubRede = pow(2, bitsParaSubRede(qtdSubRede));
    subRede* sRede = new subRede [particoesSubRede];

    int* mascaraBinario = retornaVetorzao(mascara[0], mascara[1], mascara[2], mascara[3]); //Retorna endereco em binario int[32]
    int* ipBinario = retornaVetorzao(ip[0], ip[1], ip[2], ip[3]);

    int qtdBitsSubRede = bitsParaSubRede(qtdSubRede);
    int posicaoASomarBit = zeroMascara(mascaraBinario); //inicio
    int posicaoASomarBitFinal =  posicaoASomarBit + qtdBitsSubRede; // possui erro de posicao

    int quantidadeMaquinasPorSubRede = pow(2,32-posicaoASomarBit-qtdBitsSubRede)-2;

    int i = 0, j = 0;


    bool ok = true; // so pa garantir

     for(i=0; i<particoesSubRede && ok;  i++)
    {
        for(j=0; j<32; j++)
        {
            sRede[i].IpBinSub[j] = ipBinario[j];
            sRede[i].IpBinPrimeiroValido[j] = ipBinario[j];
        }
        //Primerira maquina
        interarIpBinario(sRede[i].IpBinPrimeiroValido,0,32);


        //Proxima subRede
        ok = interarIpBinario(ipBinario, posicaoASomarBit - 1, posicaoASomarBitFinal);

        //Endereco da prox sub rede -1, e o broad cast
        for(j=0; j<32; j++)
        { // pegando o ip da prox rede
            sRede[i].IpBinBroad[j] = ipBinario[j];
        }
        // decrementa 1, para BroadCast
        decrementarIpBinario(sRede[i].IpBinBroad, 0, 32);

        ///Ultimo Host ip valido
        ///Pega o broad cast e decrementa 1
        for(j=0; j<32; j++)
        { // pegando o ip da prox rede
            sRede[i].IpBinBroad[j] = sRede[i].IpBinBroad[j];
        }
        // decrementa 1, para BroadCast
        decrementarIpBinario(sRede[i].IpBinBroad, 0, 32);

        ///Ultimo Host ip valido
        ///Pega o broad cast e decrementa 1
        for(j=0; j<32; j++)
        { // pegando o ip da prox rede
            sRede[i].IpBinUltimoValido[j] = sRede[i].IpBinBroad[j];
        }
        // decrementa 1, para BroadCast
        decrementarIpBinario(sRede[i].IpBinUltimoValido, 0, 32);
    }

    //Pegando no struct as subRedes em binario e inserindo no struct em Decimal
    for(i=0; i<particoesSubRede;  i++)
    {
      ipDecimalMontador(sRede[i].IpBinSub, sRede[i].IpDecimalSub);
    }

    //Pegando no struct Primeiro host em binario e inserindo no struct host em Decimal
    for(i=0; i<particoesSubRede;  i++)
    {
      ipDecimalMontador(sRede[i].IpBinPrimeiroValido, sRede[i].IpDecimalPrimeiroValido);
    }

    for(i=0; i<particoesSubRede;  i++)
    {
       novaMascara(mascaraBinario, sRede[i].IpMascaraBin, qtdBitsSubRede);
       ipDecimalMontador(sRede[i].IpMascaraBin, sRede[i].IpMascaraDecimal);
    }

    //Pegando no struct BroadCast em binario e inserindo no struct BroadCast em Decimal
    for(i=0; i<particoesSubRede;  i++)
    {
      ipDecimalMontador(sRede[i].IpBinBroad, sRede[i].IpDecimalBroad);
    }

    //Pegando no struct Ultimo host em binario e inserindo no struct Ultimo em Decimal
    for(i=0; i<particoesSubRede;  i++)
    {
      ipDecimalMontador(sRede[i].IpBinUltimoValido, sRede[i].IpDecimalUltimoValido);
    }

    ///Quantidade de maquinas por sub rede
    for(i=0; i<particoesSubRede;  i++)
    {
      sRede[i].maquinaNaSubRede = quantidadeMaquinasPorSubRede;
    }
    delete mascaraBinario;
    delete ipBinario;
    return sRede;
}

void redeDoIp(int* ip, int* mascara)
{
    int bitClasse = bitsRedeClasse(ip);

    int i= 0;
    for(i = bitClasse; mascara[i] == 1 && i<32; i++)
    {}

    for(i; i<32;i++)
    {
        ip[i] = 0;
    }
}

//Formatando a saida
