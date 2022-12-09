#with normal mutation
from random import randint, random
from random import shuffle
import timeit

length = 20
mutation = 0.1
count = 20
generation = 0
fitness = 0
result = [(generation,fitness)]
#print "length =",length
#print "mutation =",mutation
#print "count",count


# generate individual
def individual(length):
    return [randint(0, 1) for x in xrange(length)]


# generate population
def population(count, length):
    return [individual(length) for x in xrange(count)]


pop = population(count, length)


def sortList(list):
    newlist = sorted(list, key=lambda k: k['sum'])  # sort list according to their fitness
    return newlist

def sortPop(pop):
    dict_list = []
    for gene in pop:
        sumo = sum(gene)  # calcualate the sum
        dict = {'gene': gene, 'sum': sumo}  # create a dictionary of the gene and its fitness
        dict_list.append(dict)  # append to the list
    newlist = sorted(dict_list, key=lambda k: k['sum'])  # sort list according to their fitness
    return newlist


# calculate fitness
def calcFitness(pop, length):
    start_time = timeit.default_timer()
    # code you want to evaluate

    global generation
    global result
    for gene in pop:  # take every gene in the population
        if sum(gene) == length:  # compare if it is the fittest
            result.append((generation, sum(gene)))
            #print "The Best Generation is", generation, "with fitness:", sum(gene),",gene:", gene   # return generation  # if fittest return
            elapsed = timeit.default_timer() - start_time
            print (generation,sum(gene),elapsed)
            exit()
        #else:
    sorted_list = sortPop(pop)
    best = sorted_list[count-1]['gene']
    elapsed = timeit.default_timer() - start_time
    print generation,sum(best),elapsed
    result.append((generation,sum(best)))
    generation += 1  # increase the number of generations




# calcFitness(pop,length)
# print sorted(calcFitness(pop,length), key=lambda k: k['sum'])

def tournament(dict_list):
    i = 0
    while (i != 1):
        shuffle(dict_list)
        sum1 = dict_list[1]['sum']
        gene1 = dict_list[1]['gene']
        sum2 = dict_list[2]['sum']
        gene2 = dict_list[2]['gene']
        if sum1 > sum2:
            i = 1
            return gene1
        elif sum2 > sum1:
            i = 1
            return gene2
        else:
            i = 0

def select(dict_list):  # Select two fittest genes
    parent1 = tournament(dict_list) #parent1 = tournament(gene1,gene2)
    parent2 = tournament(dict_list)
    if parent1!=parent2:
        return parent1,parent2
    else:
        return select(dict_list)



def crossover(parent1, parent2):
    length = len(parent1)
    child1 = parent1[0:length / 2] + parent2[length / 2:length]
    child2 = parent2[0:length / 2] + parent1[length / 2:length]
    return child1, child2


def mutate(child1, child2, mutation):
    # mutation
    # mutation_rate = 0.1
    if int(mutation * 10) < randint(0, 10):
        pos_to_mutate = randint(0, len(child1) - 1)
        if child1[pos_to_mutate] == 0:
            child1[pos_to_mutate] = 1
        elif child1[pos_to_mutate] == 1:
            child1[pos_to_mutate] = 0

        if child2[pos_to_mutate] == 0:
            child2[pos_to_mutate] = 1
        elif child2[pos_to_mutate] == 1:
            child2[pos_to_mutate] = 0


    return child1, child2


def elitism(dict_list, pop):
    # copy the best two genes to new population  in the first two elements
    parent1, parent2 = select(dict_list)
    new_pop = pop
    new_pop[0] = parent1
    new_pop[1] = parent2
    return new_pop


def CreateNewPopulation(selection_list):
    for gene in range(len(selection_list)):
        gene1,gene2 = select(selection_list) #
        child1, child2 = crossover(gene1, gene2)
        xchild1, xchild2 = mutate(child1, child2, mutation)
        pop[gene] = xchild1
        pop[gene - 1] = xchild2
    return pop

#print "generation",",","fitness"
while (1):
    dict_list = sortPop(pop)  # gives back the dictionary of individuals and their sums
    elit_pop = elitism(dict_list,pop)  # gives back the population where the best two individuals are assigned to the first two elements on the list
    #new_pop = elit_pop[2:len(elit_pop)]# Assigning all other individuals other than first two to another variable list
    new_list = sortPop(elit_pop) #sorting the new population

    #elit_pop[2:len(elit_pop)] = CreateNewPopulation(new_list)  # Sending that variable list to create new population by applying crossover and mutation and adding the elitism best two individuuals
    pop = CreateNewPopulation(new_list)  # assign the new population to replace the old population
    calcFitness(pop,length)


