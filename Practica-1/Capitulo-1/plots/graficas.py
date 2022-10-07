import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Función para hacer plot de las gráficas
def graficar(data, plot_type, x, y, x_label, y_label, title, archivo_name):
    data.plot(x=x, y=y, kind=plot_type, title=title, figsize=(8,8))
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.savefig(
        f'/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/plots/{archivo_name}.png', )
    # plt.show()


# # Grafica de la ganancia media en funcion de las veces que se tira la moneda
# df_gananciamedia = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-cantidad.csv',sep=',')

# medias = df_gananciamedia.groupby('Veces').mean()

# graficar(medias, 'bar', None, 'Esperado', 'Veces', 'Ganancia Media', 'Ganancia Media vs Veces', 'ganancia-media-vs-veces')

# # Grafica de la ganancia media vs la cantidad de veces que se lanzó la moneda
# df_prob = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-prob.csv',sep=',')

# graficar(df_prob, 'scatter', 'Probabilidad', 'Esperado', 'Probabilidad', 'Ganancia Final', 'Ganancia vs Probabilidad', 'ganancia-vs-probabilidad')

# # Grafica de la ganancia obtenida en funcion de la diferencia para terminar de lanzar
# df_diff = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-diff.csv',sep=',')

# diferencias = df_diff.groupby('Diferencia').mean()

# graficar(diferencias, 'scatter', None, 'Esperado', 'Diferencia', 'Ganancia Media', 'Ganancia Media vs Diferencia', 'ganancia-media-vs-diferencia')

# Variación del pago por lanzamiento (pago finalizar fijo a 100)
# df = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-yz.csv',sep=',')

# pago_finalizar_fijo = df[['Pago_Lanzamiento', 'Pago_Finalizar', 'Esperado']].groupby('Pago_Lanzamiento')[['Esperado', 'Pago_Lanzamiento']]

# graficar(pago_finalizar_fijo, 'bar', None, 'Esperado', 'Pago por lanzamiento', 'Ganancia Media', 'Ganancia media variando el pago por lanzamiento', 'ganancia-media-vs-pago-lanzamiento')

# print(pago_finalizar_fijo.head())


# # Variación del pago por finalizar (pago lanzamiento fijo a 10)
# pago_lanzamiento_fijo = df[['Pago_Lanzamiento', 'Pago_Finalizar', 'Esperado']].groupby('Pago_Finalizar')[['Esperado', 'Pago_Lanzamiento']]

# print(pago_lanzamiento_fijo.head())

# graficar(pago_lanzamiento_fijo, 'bar', None, 'Esperado', 'Pago por finalizar', 'Ganancia Media', 'Ganancia media variando el pago por finalizar', 'ganancia-media-vs-pago-finalizar')