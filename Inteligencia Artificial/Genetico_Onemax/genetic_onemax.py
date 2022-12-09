import random
import copy

class resposta:
    def __init__(self,s):
        self.s = s
        self.ava=self.avaliacao(s)
        self.normalizacao = 0

    def avaliacao(self,s):
        avaliacao = 0
        for i in range(len(s)):
            avaliacao = avaliacao + s[i]
        return avaliacao

    def get_avaliacao(self):
        return self.ava

    def setNormalizacao(self, valor):
        self.normalizacao = valor

    def avaliar(self):
        self.ava = avaliacao(self.s)

    def __str__(self) -> str:
        print(self.s)


def GA(max_iter, populacao, dimensao):
    populacao = []
    t = 0
    solucao = []

    for i in range(populacao):
        s = []
        for j in range(dimensao):
            aux = random.random()
            if aux < 0.5:
                s.append(1)
            else:
                s.append(0)
        solucao.append(resposta(s))

def avaliacao(resposta):
    for i in range(len(resposta)):
        resposta[i].avaliar
