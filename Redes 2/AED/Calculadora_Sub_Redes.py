from tkinter import *

#Calculadora de SubRedes
class Application:
    def __init__(self, master=None):
        self.fontePadrao = ("Arial", "10")
        self.primeiroContainer = Frame(master)
        self.primeiroContainer["pady"] = 10
        self.primeiroContainer.pack()

        self.segundoContainer = Frame(master)
        self.segundoContainer["padx"] = 20
        self.segundoContainer.pack()

        self.terceiroContainer = Frame(master)
        self.terceiroContainer["padx"] = 20
        self.terceiroContainer.pack()

        self.quartoContainer = Frame(master)
        self.quartoContainer["pady"] = 20
        self.quartoContainer.pack()

        self.quintoContainer = Frame(master)
        self.quintoContainer["pady"] = 20
        self.quintoContainer.pack()

        self.sextoContainer = Frame(master)
        self.sextoContainer["pady"] = 20
        self.sextoContainer.pack()

        self.setimoContainer = Frame(master)
        self.setimoContainer["pady"] = 20
        self.setimoContainer.pack()

        self.oitavoContainer = Frame(master)
        self.oitavoContainer["pady"] = 20
        self.oitavoContainer.pack()

        self.nonoContainer = Frame(master)
        self.nonoContainer["pady"] = 20
        self.nonoContainer.pack()

        self.decimoContainer = Frame(master)
        self.decimoContainer["pady"] = 20
        self.decimoContainer.pack()

        self.onzeContainer = Frame(master)
        self.onzeContainer["pady"] = 20
        self.onzeContainer.pack()

        self.dozeContainer = Frame(master)
        self.dozeContainer["pady"] = 20
        self.dozeContainer.pack()

        self.titulo = Label(self.primeiroContainer, text="Calculadora Sub-Redes")
        self.titulo["font"] = ("Arial", "10", "bold")
        self.titulo.pack()

        self.ipLabel = Label(self.segundoContainer, text="Ip", font=self.fontePadrao)
        self.ipLabel.pack(side=LEFT)

        self.Ip = Entry(self.segundoContainer)
        self.Ip["width"] = 30
        self.Ip["font"] = self.fontePadrao
        self.Ip.pack(side=LEFT)

        self.mascaraLabel = Label(self.terceiroContainer, text="Mascara de Rede", font=self.fontePadrao)
        self.mascaraLabel.pack(side=LEFT)

        self.mascara = Entry(self.terceiroContainer)
        self.mascara["width"] = 30
        self.mascara["font"] = self.fontePadrao
        self.mascara.pack(side=LEFT)

        self.mascaraRedeLabel = Label(self.terceiroContainer, text="  Máscara de Sub-Rede", font=self.fontePadrao)
        self.mascaraRedeLabel.pack(side=LEFT)

        self.mascaraRede = Entry(self.terceiroContainer)
        self.mascaraRede["width"] = 30
        self.mascaraRede["font"] = self.fontePadrao
        self.mascaraRede.pack(side=LEFT)

        self.autenticar = Button(self.quartoContainer)
        self.autenticar["text"] = "Calcular"
        self.autenticar["font"] = ("Calibri", "8")
        self.autenticar["width"] = 15
        self.autenticar["command"] = self.calcularIP
        self.autenticar.pack()

        self.autenticar = Button(self.quartoContainer)
        self.autenticar["text"] = "Calcular Sub-Redes"
        self.autenticar["font"] = ("Calibri", "8")
        self.autenticar["width"] = 15
        self.autenticar["command"] = self.calcularSubRedes
        self.autenticar.pack()

        self.mensagem = Label(self.quartoContainer, text="", font=self.fontePadrao)
        self.mensagem.pack()

        self.mensagem2 = Label(self.quintoContainer, text="", font=self.fontePadrao)
        self.mensagem2.pack()

        self.mensagem3 = Label(self.sextoContainer, text="", font=self.fontePadrao)
        self.mensagem3.pack()

        self.mensagem4 = Label(self.setimoContainer, text="", font=self.fontePadrao)
        self.mensagem4.pack()

        self.mensagem5 = Label(self.oitavoContainer, text="", font=self.fontePadrao)
        self.mensagem5.pack()

        self.mensagem6 = Label(self.nonoContainer, text="", font=self.fontePadrao)
        self.mensagem6.pack()

        self.mensagem7 = Label(self.decimoContainer, text="", font=self.fontePadrao)
        self.mensagem7.pack()

        self.mensagem8 = Label(self.onzeContainer, text="", font=self.fontePadrao)
        self.mensagem8.pack()

        self.mensagem9 = Label(self.dozeContainer, text="", font=self.fontePadrao)
        self.mensagem9.pack()

        # Método verificar senha

    def calcularIP(self):
        ip = self.Ip.get()
        mascaraRede = self.mascaraRede.get()
        mascara = self.mascara.get()
        valueMasc = int(mascara)
        if validate_ip(ip) and valueMasc > 7 and valueMasc < 31 and len(mascara)!=0:

            # PRIMEIRA LINHA IP
            finalIP = "IP: " + ip + " | " + mostrarIpBin(ip)
            self.mensagem["text"] = finalIP

            # SEGUNDA LINHA MASCARA
            finalMasc = "Máscara: " + mostrarMascDec(int(mascara)) + "| " + mostrarMascBin(int(mascara))
            self.mensagem2["text"] = finalMasc

            # Terceira Linha SUBREDE
            ipBinario = mostrarIpBin(ip)
            mascaraBinario = mostrarMascBin(mascara)
            subRedeBinario = calcularSubRedes(ipBinario, mascaraBinario)
            subRedeDecimal = mostrarIpDecimal(subRedeBinario)
            self.mensagem3["text"] = "Sub-Rede: " + subRedeDecimal + "| " + subRedeBinario

            # Quarta Linha Endereço BroadCast
            broadCastBinario = broadCastSubRede(subRedeBinario, valueMasc)
            broadCastDecimal = mostrarIpDecimal(broadCastBinario)
            self.mensagem4["text"] = "BroadCast: " + broadCastDecimal + "| " + broadCastBinario

            # Quinta Linha Primeiro Host
            primHostBin = primeiroHostBinario(subRedeBinario)
            primHostDecimal = mostrarIpDecimal(primHostBin)
            self.mensagem5["text"] = "Primeiro Host: " + primHostDecimal + " | " + primHostBin

            # SEXTA LINHA ULTIMO HOST = BROADCAST - 1
            ultimoHostBin = ultimoHostBinario(broadCastBinario)
            ultimoHostDec = mostrarIpDecimal(ultimoHostBin)
            self.mensagem6["text"] = "Último Host: " + ultimoHostDec + " | " + ultimoHostBin

            # SETIMA LINHA QUANTIDADE DE HOSTS!
            quantidade = qtdHosts(valueMasc)
            self.mensagem7["text"] = "A quantidade de Hosts de "+ip+"/"+mascara+" é " + quantidade

        else:
            self.mensagem["text"] = 'Dados inválidos, favor digitar novamente!' + mascaraRede
            self.mensagem2['text'] = ""
            self.mensagem3['text'] = ""
            self.mensagem4['text'] = ""
            self.mensagem5['text'] = ""
            self.mensagem6['text'] = ""
            self.mensagem7['text'] = ""
            self.mensagem8['text'] = ""


    def calcularSubRedes(self):
        ip = self.Ip.get()
        mascaraRede = self.mascaraRede.get()
        valueMascRede = int(mascaraRede)
        mascara = self.mascara.get()
        valueMasc = int(mascara)

        qtdSubRedes = int(2**(valueMascRede - valueMasc))
        quantidade = int(qtdHosts(valueMasc)) + 2

        ipBinario = mostrarIpBin(ip)
        mascaraBinario = mostrarMascBin(mascara)
        subRedeBinario = calcularSubRedes(ipBinario, mascaraBinario)
        subRedeDecimal = mostrarIpDecimal(subRedeBinario)
        res = ""

        if valueMascRede > valueMasc and valueMascRede<31:

            auxiliar = int(quantidade / qtdSubRedes)

            ips_split = subRedeDecimal.split(" ")

            top = Tk()
            sb = Scrollbar(top, width=20)
            sb.pack(side=RIGHT, fill=Y)
            mylist = Listbox(top, yscrollcommand=sb.set, width="60", height='40')
            cont = 0
            texto = ""

            for i in range(0, qtdSubRedes):
                for j in range(0, 4):
                    res += bin8(int(ips_split[j]))


                mylist.insert(END, "SubRede: " + str((i+1)) + "\n")
                cont +=1

                mylist.insert(END, "Endereço: " + mostrarIpDecimal(res) + "/" + mascaraRede + " | "+res + "\n")
                ips_split[3] = str( int(ips_split[3]) + auxiliar -1 )
                res=""

                for z in range(0, 4):
                    res += bin8(int(ips_split[z]))
                ips_split[3] = str(int(ips_split[3]) +1)

                #texto+= "BroadCast: "+ mostrarIpDecimal(res)+ "\n"
                mylist.insert(END, "BroadCast: "+ mostrarIpDecimal(res)+ " | "+ res +"\n\n")
                mylist.insert(END, "-"*80)
                res = ""
            self.mensagem8['text'] = 'Quantidade de Sub-Redes: '+ str(cont)
            self.mensagem9['text'] = 'Quantidade de hosts por Sub-Rede:'+str(auxiliar-2)
            mylist.pack(side=LEFT)
        else:
            self.mensagem['text'] = 'Valor de máscara de rede inválido!'
            self.mensagem2['text'] = ""
            self.mensagem3['text'] = ""
            self.mensagem4['text'] = ""
            self.mensagem5['text'] = ""
            self.mensagem6['text'] = ""
            self.mensagem7['text'] = ""
            self.mensagem8['text'] = ""
            self.mensagem9['text'] = ""


bin8 = lambda x: ''.join(reversed([str((x >> i) & 1) for i in range(8)]))


def mostrarIpBin(ip):  # retorna ip em binario

    ip_split = ip.split('.')
    res = ''
    for i in ip_split:
        res += bin8(int(i))
    return res


def mostrarMascBin(mascara):  # retorna valor da mascara em binario
    val = ""
    mascara = int(mascara)

    for i in range(0, mascara+1):
        val += "1"

    for j in range(mascara, 32):
        val += "0"
    return val


def mostrarMascDec(mascara):  # mostra a mascara em decimal
    mascBin = mostrarMascBin(mascara)
    mascBin = str(mascBin)
    resFinal = ""
    split_strings = [mascBin[index: index + 8] for index in range(1, len(mascBin), 8)]  # separa a string de 8 em 8
    for i in split_strings:
        result = int(i, 2)  # transforma valor de binário para decimal
        resFinal += str(result)
        resFinal += " "
    return resFinal


def mostrarIpDecimal(bin):
    resFinal = ""
    split_strings = [bin[index: index + 8] for index in range(0, len(bin), 8)]  # separa a string de 8 em 8
    for i in split_strings:
        result = int(i, 2)  # transforma valor de binário para decimal
        resFinal += str(result)
        resFinal += " "
    return resFinal


def validate_ip(s):
    a = s.split('.')
    if len(a) != 4 and len(s) < 7 and len(s) < 15:
        return False
    for x in a:
        if not x.isdigit():
            return False
        i = int(x)
        if i < 0 or i > 255:
            return False
    return True


def broadCastSubRede(subRedeBin, mascara):
    subRedeBin = str(subRedeBin)
    final = ""
    for i in range(0, len(subRedeBin)):
        if i >= mascara:
            final += "1"
        else:
            final += subRedeBin[i]
    return final


def calcularSubRedes(ip, mascara):  # retorna texto
    listaResultados = ""

    for i in range(0, len(ip)):

        if ip[i] == mascara[i] == "1":
            listaResultados += "1"
        else:
            listaResultados += "0"
    subRede = listaResultados
    return subRede


def primeiroHostBinario(subRede):
    split_strings = [subRede[index: index + 8] for index in range(0, len(subRede), 8)]
    primHostBin = ""
    ultimo = int(split_strings[3], 2) + 1
    split_strings[3] = str(bin8(ultimo))

    for i in split_strings:
        primHostBin += i

    return primHostBin


def ultimoHostBinario(broad):  # retorna texto
    split_strings = [broad[index: index + 8] for index in range(0, len(broad), 8)]
    finalHostBin = ""
    ultimo = int(split_strings[3], 2) - 1
    split_strings[3] = str(bin8(ultimo))

    for i in split_strings:
        finalHostBin += i

    return finalHostBin


def qtdHosts(mascara): # pode ser 2^ a 32-mascara
    eleva = 32 - mascara
    qtdTotal = (2**eleva) - 2

    return str(qtdTotal)


root = Tk()
Application(root)
root.mainloop()

