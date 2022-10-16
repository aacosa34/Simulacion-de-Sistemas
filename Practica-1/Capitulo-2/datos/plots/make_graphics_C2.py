import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

pd.set_option('display.max_columns', None)

# Función para hacer plot de las gráficas
def graficar(data, plot_type, x, y, x_label, y_label, title, archivo_name):
    data.plot(x=x, y=y, kind=plot_type, title=title, figsize=(12, 12))
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.savefig(
        f'/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-2/datos/plots/{archivo_name}.png', )
    # plt.show()

# Abrir los datos
politica1 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-2/datos/simulacion-politica1.csv')
politica2 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-2/datos/simulacion-politica2.csv')
politica3 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-2/datos/simulacion-politica3.csv')

# Graficar los datos
# Grafica politica 1
df_p1 = politica1.groupby(['Veces'])

print(df_p1.get_group(500))

for vez, tabla in df_p1:
    graficar(tabla, 'bar', 's-S', ['M-CostoTotal', 'M-CostoPedido', 'M-CostoMantenimiento', 'M-CostoDeficit'],
             'Politica', 'Costo', f'Inventario 1 - Veces simuladas: {vez}', f'inventario-1/inventario1-{vez}veces')
# Grafica inventario 2
df_p2 = politica2.groupby(['Veces']).mean()

graficar(df_p2, 'bar', None, ['M-CostoTotal', 'M-CostoPedido', 'M-CostoMantenimiento', 'M-CostoDeficit'], 'Veces Simuladas', 'Costo', 'Inventario 2', 'inventario-2/inventario2')

# Grafica politica 3
df_p3 = politica3.groupby(['Veces'])

print(df_p3.get_group(500))

for vez, tabla in df_p3:
    graficar(tabla, 'bar', 's-S', ['M-CostoTotal', 'M-CostoPedido', 'M-CostoMantenimiento', 'M-CostoDeficit'],
             'Politica', 'Costo', f'Inventario 3 - Veces simuladas: {vez}', f'inventario-3/inventario3-{vez}veces')

