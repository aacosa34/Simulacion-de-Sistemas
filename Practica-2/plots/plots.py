from plotly.offline import iplot
import plotly.graph_objects as go
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df_base = pd.read_csv(
    "/home/adrian/Dev/Simulacion-de-Sistemas/Practica-2/data/base.csv", sep="\t")
df_mejora1 = pd.read_csv(
    "/home/adrian/Dev/Simulacion-de-Sistemas/Practica-2/data/mejora1.csv", sep="\t")
df_mejora2 = pd.read_csv(
    "/home/adrian/Dev/Simulacion-de-Sistemas/Practica-2/data/mejora2.csv", sep="\t")
df_mejora3 = pd.read_csv(  
    "/home/adrian/Dev/Simulacion-de-Sistemas/Practica-2/data/mejora3.csv", sep="\t")


# dict for the dataframes and their names
dfs = {"df1": df_base, "df2": df_mejora1, "df3": df_mejora2, "df4": df_mejora3}

# plot the data
fig = go.Figure()

for i in dfs:
    fig = fig.add_trace(go.Scatter(x=dfs[i]["reps"],
                                   y=dfs[i]["tiempo"],
                                   name= i,
                                   title='Tiempo de ejecución frente a numero de repeticiones'))
fig.show()


