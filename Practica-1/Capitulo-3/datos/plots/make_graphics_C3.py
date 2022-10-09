import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Función para hacer plot de las gráficas


def graficar(data, plot_type, x, y, x_label, y_label, title, filename):
    data.plot(x=x, y=y, kind=plot_type, title=title, figsize=(10, 10))
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.savefig(
        f'/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/plots/{filename}.png')
    # plt.show()


# Data Frames apartado 1
df_apartado_1_1 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/apartado-1/simulacion_10000_125.csv', sep='\t')
df_apartado_1_2 = pd.read_csv(
    '/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/apartado-1/simulacion_10000_200.csv', sep='\t')

# Data Frames apartado 2
df_pesca_25 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/apartado-2/campania_pesca_25.csv', sep='\t')
df_pesca_50 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/apartado-2/campania_pesca_50.csv', sep='\t')
df_pesca_75 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/apartado-2/campania_pesca_75.csv', sep='\t')

# # Data Frames apartado 3
df_periodo_91 = pd.read_csv(
    '/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/apartado-3/periodo_91.csv', sep='\t')
df_periodo_182 = pd.read_csv(
    '/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/apartado-3/periodo_182.csv', sep='\t')
df_periodo_365 = pd.read_csv(
    '/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/apartado-3/periodo_365.csv', sep='\t')
df_periodo_730 = pd.read_csv(
    '/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/apartado-3/periodo_730.csv', sep='\t')
df_periodo_1460 = pd.read_csv(
    '/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-3/datos/apartado-3/periodo_1460.csv', sep='\t')


# Graficas apartado 1
# Apartado 1 125 peces grandes
graficar(df_apartado_1_1, 'line', 't', 'x', 'Tiempo (días)', 'Peces pequeños', 'Crecimiento de peces pequeños con respecto al tiempo', 'apartado-1/peces_pequenos_125')
graficar(df_apartado_1_1, 'line', 't', 'y', 'Tiempo (días)', 'Peces grandes',
         'Crecimiento de peces grandes con respecto al tiempo', 'apartado-1/peces_grandes_125')
graficar(df_apartado_1_1, 'line', 'y', 'x', 'Peces grandes', 'Peces pequeños',
         'Crecimiento de peces pequeños y grandes', 'apartado-1/peces_pequenos_grandes_125')

# Apartado 1 200 peces grandes
graficar(df_apartado_1_2, 'line', 't', 'x', 'Tiempo (días)', 'Peces pequeños',
         'Crecimiento de peces pequeños con respecto al tiempo', 'apartado-1/peces_pequenos_200')
graficar(df_apartado_1_2, 'line', 't', 'y', 'Tiempo (días)', 'Peces grandes',
         'Crecimiento de peces grandes con respecto al tiempo', 'apartado-1/peces_grandes_200')

# Graficas apartado 2
graficar(df_pesca_25, 'line', 't', 'x', 'Tiempo (días)', 'Peces pequeños', 'Crecimiento de peces pequeños con respecto al tiempo', 'apartado-2/pequenyos_pesca_25')
graficar(df_pesca_25, 'line', 't', 'y', 'Tiempo (días)', 'Peces grandes',
         'Crecimiento de peces grandes con respecto al tiempo', 'apartado-2/grandes_pesca_25')
graficar(df_pesca_25, 'line', 'y', 'x', 'Peces grandes', 'Peces pequeños', 'Crecimiento de peces pequeños y grandes', 'apartado-2/pequenyos_grandes_pesca_25')

graficar(df_pesca_50, 'line', 't', 'x', 'Tiempo (días)', 'Peces pequeños',
         'Crecimiento de peces pequeños con respecto al tiempo', 'apartado-2/pequenyos_pesca_50')
graficar(df_pesca_50, 'line', 't', 'y', 'Tiempo (días)', 'Peces grandes',
         'Crecimiento de peces grandes con respecto al tiempo', 'apartado-2/grandes_pesca_50')
graficar(df_pesca_50, 'line', 'y', 'x', 'Peces grandes', 'Peces pequeños', 'Crecimiento de peces pequeños y grandes', 'apartado-2/pequenyos_grandes_pesca_50')

graficar(df_pesca_75, 'line', 't', 'x', 'Tiempo (días)', 'Peces pequeños',
         'Crecimiento de peces pequeños con respecto al tiempo', 'apartado-2/pequenyos_pesca_75')
graficar(df_pesca_75, 'line', 't', 'y', 'Tiempo (días)', 'Peces grandes',
         'Crecimiento de peces grandes con respecto al tiempo', 'apartado-2/grandes_pesca_75')
graficar(df_pesca_75, 'line', 'y', 'x', 'Peces grandes', 'Peces pequeños', 'Crecimiento de peces pequeños y grandes', 'apartado-2/pequenyos_grandes_pesca_75')

# Graficas apartado 3

df_apartado_3 = pd.DataFrame({
    'Periodos': ['Cada 4 meses', 'Cada 6 meses', 'Cada año', 'Cada 2 años', 'Cada 4 años'],
    'Valores': [df_periodo_91['pescados'].tail(1).values[0],
                df_periodo_182['pescados'].tail(1).values[0], 
                df_periodo_365['pescados'].tail(1).values[0], 
                df_periodo_730['pescados'].tail(1).values[0], 
                df_periodo_1460['pescados'].tail(1).values[0]]
})

graficar(df_apartado_3, 'bar', 'Periodos', 'Valores', 'Periodo de tiempo', 'Cantidad de peces', 'Cantidad de peces en función de la campaña de pesca', 'apartado-3/pescados_por_periodo')
graficar(df_periodo_91, 'line', 't', 'x', 'Tiempo (días)', 'Peces pequeños', 'Crecimiento de peces pequeños con respecto al tiempo', 'apartado-3/pequenyos_periodo_91')
graficar(df_periodo_91, 'line', 't', 'y', 'Tiempo (días)', 'Peces grandes', 'Crecimiento de peces grandes con respecto al tiempo', 'apartado-3/grandes_periodo_91')
graficar(df_periodo_91, 'line', 'y', 'x', 'Peces grandes', 'Peces pequeños', 'Crecimiento de peces pequeños y grandes', 'apartado-3/pequenyos_grandes_periodo_91')