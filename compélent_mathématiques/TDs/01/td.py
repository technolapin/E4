import scipy.stats as stats
import numpy as np
import pandas
import matplotlib.pyplot as plt


def ExerciceI():
    n1 = 254
    n2 = 362
    x1_emp = 28 # espérance empirique
    x2_emp = 28.5
    s1 = 4.9 # ecart-type empirique
    s2 = 4.5

    # on traîte le cas 2
    n = n2
    m2 = x1_emp # hypothèse
    Xn_emp = x2_emp # on vérifie si ça marche avec x1
    Sn2 = s2
    # t est la valeur de la statistique T
    t = np.sqrt(n)*(Xn_emp - m2)/Sn2
    print(t)

    alpha = 0.05
    calpha = stats.t.ppf(1 - alpha/2, n-1)
    print(calpha)



def ExerciceII():
    data = pandas.read_csv("tdexo2data.csv")
    data.head()
    x = data["#Tav"]
    y = data["Tap"]
    #print(y)
    bp11 = plt.figure()
    plt.boxplot([x,y], sym='b+', medianprops=dict(color='red'))
    plt.title("boîte à moustache")
     plt.show(bp11)

    henry = plt.figure()
    stats.probplot(x-y, dist='norm', plot=plt)
    plt.xlabel("quantiles théoriques")
    plt.ylabel("quantiles de l'échantillon")
    plt.title("Droite de Henry")
    plt.show(henry)
ExerciceII()
