import numpy as np
from scipy.stats import t


def transform_to_float(input_str):
    floats = list(map(lambda x: float(x), input_str.split()))

    return floats


def calcular_intervalo_confianza(sistA, sistB, n, alfa):
    dif_a_b = sistA[:n] - sistB[:n]

    media = np.mean(dif_a_b)
    var = np.var(dif_a_b, ddof=1)

    print(f"\nMedia: {media}")
    print(f"Varianza: {var}")
    print(f"N: {n}")
    print(f"alfa: {alfa}")

    t_values = t.interval(1-alfa, n-1)

    intervalo = [media + t * np.sqrt(var/n) for t in t_values]
    print(f"Intervalo obtenido: {intervalo}")


# Leer los ficheros
with open("data/ejer3/3-2/sistema_a_estancia.txt") as sist_a, open("data/ejer3/3-2/sistema_b_estancia.txt") as sist_b:
    s_a = np.array(transform_to_float(sist_a.read()))
    s_b = np.array(transform_to_float(sist_b.read()))


calcular_intervalo_confianza(s_a, s_b, 20, 0.05)
calcular_intervalo_confianza(s_a, s_b, 40, 0.05)
calcular_intervalo_confianza(s_a, s_b, 60, 0.05)
calcular_intervalo_confianza(s_a, s_b, 80, 0.05)
calcular_intervalo_confianza(s_a, s_b, 100, 0.05)
