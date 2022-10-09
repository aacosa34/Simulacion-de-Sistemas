import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

pd.set_option('display.max_columns', None)

# Función para hacer plot de las gráficas
def graficar(data, plot_type, x, y, x_label, y_label, title, archivo_name):
    data.plot(x=x, y=y, kind=plot_type, title=title, figsize=(12,12))
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.savefig(
        f'/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/plots/{archivo_name}.png', )
    # plt.show()

# Lectura de los datos
# Primer apartado
cantidad = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-cantidad.csv', sep=',')
# Segundo apartado
y10_z1000 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-10-1000.csv', sep=',')
y100_z100 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-100-100.csv', sep=',')
y100_z1000 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-100-1000.csv', sep=',')
y1000_z100 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-1000-100.csv', sep=',')
y1000_z1000 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-1000-1000.csv', sep=',')
y1000_z10000 = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-1000-10000.csv', sep=',')
# Tercer apartado
prob = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-prob.csv', sep=',')
diff = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-diff.csv', sep=',')

ambas = pd.read_csv('/home/adrian/Dev/Simulacion-de-Sistemas/Practica-1/Capitulo-1/datos/lanzamientos-ambas.csv', sep=',')

# Graficar ganancia media por numero de lancamientos
ganancia_cantidad = cantidad.groupby('Veces').mean()
graficar(ganancia_cantidad, 'bar', None, 'Esperado', 'Veces', 'Ganancia Media', 'Ganancia Media vs Veces', '1-ganancia-media-vs-veces')

# Ganancia en función de los valores de 'y' y 'z'
df_yz = pd.DataFrame({
    'Pago partida/final': ['10/1000', '100/100', '100/1000', '1000/100', '1000/1000', '1000/10000'],
    'Ganancia': [y10_z1000['Esperado'].mean(), y100_z100['Esperado'].mean(), y100_z1000['Esperado'].mean(), y1000_z100['Esperado'].mean(), y1000_z1000['Esperado'].mean(), y1000_z10000['Esperado'].mean()]
})
graficar(df_yz, 'bar', 'Pago partida/final', 'Ganancia', 'Pago por partida / Pago al finalizar', 'Ganancia Media', 'Ganancia Media vs Valores de y y z', '2-ganancia-media-vs-y-z')

# Grafica de la ganancia media vs la cantidad de veces que se lanzó la moneda

graficar(prob, 'line', 'Probabilidad', 'Esperado', 'Probabilidad', 'Ganancia Final', 'Ganancia vs Probabilidad', '3-ganancia-vs-probabilidad')

# Grafica de la ganancia obtenida en funcion de la diferencia para terminar de lanzar

diferencias = diff.groupby('Diferencia').mean()

graficar(diferencias, 'line', None, 'Esperado', 'Diferencia', 'Ganancia Media', 'Ganancia Media vs Diferencia', '3-ganancia-media-vs-diferencia')

# Grafica de ganancia cambiando ambas variables

ax = plt.axes(projection='3d')

x = ambas['Probabilidad'].values
y = ambas['Diferencia'].values
z = ambas['Esperado'].values
plt.xlabel('Probabilidad')
plt.ylabel('Diferencia')
ax.set_zlabel('Ganancia')
ax.scatter3D(x, y, z)
plt.show()
