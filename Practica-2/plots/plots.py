import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df_base = pd.read_csv(
    "/home/adrian/Dev/Simulacion-de-Sistemas/Practica-2/data/base.csv", encoding='utf-8', sep="\t")
df_mejora1 = pd.read_csv(
    "/home/adrian/Dev/Simulacion-de-Sistemas/Practica-2/data/mejora1.csv", sep="\t")
df_mejora2 = pd.read_csv(
    "/home/adrian/Dev/Simulacion-de-Sistemas/Practica-2/data/mejora2.csv", sep="\t")
df_mejora3 = pd.read_csv(  
    "/home/adrian/Dev/Simulacion-de-Sistemas/Practica-2/data/mejora3.csv", sep="\t")


# dict for the dataframes and their names
dfs = [df_base, df_mejora1, df_mejora2, df_mejora3]

fig = plt.figure()

for data in dfs:
    plt.plot(data['reps'], data['tiempo'], marker='o')

plt.xlabel('Repeticiones')
plt.ylabel('Tiempo (s)')
plt.title('Tiempo de ejecución en función de las repeticiones')
plt.legend(['Base', 'Mejora 1', 'Mejora 2', 'Mejora 3'])
plt.grid()
plt.show()