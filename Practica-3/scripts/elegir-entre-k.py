import numpy as np
import math


def transform_to_float(file):
    with open(file) as f:
        input_str = f.read()

        floats = list(map(lambda x: float(x), input_str.split()))

    return np.array(floats)


def calcular_w1(h, var, d, n0, N):
    val_1 = 1 - ((N-n0)*d*d)/(h*h*var)
    print(val_1, N/n0)
    val_2 = math.sqrt(1 - (N/n0)*val_1)
    val_3 = 1 + val_2
    val_4 = (n0/N)*val_3

    return val_4


def calcula_w1_w2(n0, N, d, h1, s):
    val1 = 1 - ((N-n0)*d**2)/(s*h1**2)
    val2 = np.sqrt(1 - (N/n0)*val1)
    val3 = 1 + val2

    w1 = (n0/N) * val3
    w2 = 1 - w1

    return w1, w2


operarios1 = transform_to_float("data/ejer3/3-3/estancia-operarios1.txt")
operarios2 = transform_to_float("data/ejer3/3-3/estancia-operarios2.txt")
operarios5 = transform_to_float("data/ejer3/3-3/estancia-operarios5.txt")
operarios10 = transform_to_float("data/ejer3/3-3/estancia-operarios10.txt")

n0 = 40
d = 0.05
h1 = 3.003
k = 4

media_operarios1_1 = np.mean(operarios1[:n0])
media_operarios2_1 = np.mean(operarios2[:n0])
media_operarios5_1 = np.mean(operarios5[:n0])
media_operarios10_1 = np.mean(operarios10[:n0])

var_operarios1 = np.var(operarios1[:n0], ddof=1)
var_operarios2 = np.var(operarios2[:n0], ddof=1)
var_operarios5 = np.var(operarios5[:n0], ddof=1)
var_operarios10 = np.var(operarios10[:n0], ddof=1)

N_operarios1 = int(max(n0+1, np.round((h1**2 * var_operarios1) / d**2)))
N_operarios2 = int(max(n0+1, np.round((h1**2 * var_operarios2) / d**2)))
N_operarios5 = int(max(n0+1, np.round((h1**2 * var_operarios5) / d**2)))
N_operarios10 = int(max(n0+1, np.round((h1**2 * var_operarios10) / d**2)))

media_operarios1_2 = np.mean(operarios1[n0:N_operarios1])
media_operarios2_2 = np.mean(operarios2[n0:N_operarios2])
media_operarios5_2 = np.mean(operarios5[n0:N_operarios5])
media_operarios10_2 = np.mean(operarios10[n0:N_operarios10])

w1_operarios1, w2_operarios1 = calcula_w1_w2(
    n0, N_operarios1, d, h1, var_operarios1)
w1_operarios2, w2_operarios2 = calcula_w1_w2(
    n0, N_operarios2, d, h1, var_operarios2)
w1_operarios5, w2_operarios5 = calcula_w1_w2(
    n0, N_operarios5, d, h1, var_operarios5)
w1_operarios10, w2_operarios10 = calcula_w1_w2(
    n0, N_operarios10, d, h1, var_operarios10)

xp_operarios1 = w1_operarios1 * media_operarios1_1 + \
    w2_operarios1 * media_operarios1_2
xp_operarios2 = w1_operarios2 * media_operarios2_1 + \
    w2_operarios2 * media_operarios2_2
xp_operarios5 = w1_operarios5 * media_operarios5_1 + \
    w2_operarios5 * media_operarios5_2
xp_operarios10 = w1_operarios10 * media_operarios10_1 + \
    w2_operarios10 * media_operarios10_2

print(f"n0: {n0}")
print(
    f"10 maquinas, 1 operario -> media 1: {media_operarios1_1:.3f} var: {var_operarios1:.8f} N: {N_operarios1} media 2: {media_operarios1_2:.3f} w1: {w1_operarios1:.3f} w2: {w2_operarios1:.3f} xp: {xp_operarios1:.3f}")
print(
    f"10 maquinas, 2 operarios -> media 1: {media_operarios2_1:.3f} var: {var_operarios2:.8f} N: {N_operarios2} media 2: {media_operarios2_2:.3f} w1: {w1_operarios2:.3f} w2: {w2_operarios2:.3f} xp: {xp_operarios2:.3f}")
print(
    f"10 maquinas, 5 operarios -> media 1: {media_operarios5_1:.3f} var: {var_operarios5:.3f} N: {N_operarios5} media 2: {media_operarios5_2:.3f} w1: {w1_operarios5:.3f} w2: {w2_operarios5:.3f} xp: {xp_operarios5:.3f}")
print(
    f"10 maquinas, 10 operarios -> media 1: {media_operarios10_1:.3f} var: {var_operarios10:.3f} N: {N_operarios10} media 2: {media_operarios10_2:.3f} w1: {w1_operarios10:.3f} w2: {w2_operarios10:.3f} xp: {xp_operarios10:.3f}")
