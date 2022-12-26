#include <iostream>
#include <cstdlib>

using namespace std;

double uniforme()
{
    int t = random();
    double f = ((double)RAND_MAX + 1.0);
    return (double)t / f;
}

int genera_demanda(int *demandas, double *probabilidades)
{
    double u = uniforme();
    int i = 0;
    while (u >= probabilidades[i])
    {
        i++;
    }
    return demandas[i];
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        cerr << "Formato " << argv[0] << " <num_veces>" << endl;
        return -1;
    }
    int num_veces = atoi(argv[1]);

    // Definimos las demandas y sus probabilidades en funcion del precio por lata
    int demandas[] = {50, 90, 130, 170};
    double prob_precio1[] = {0.1, 0.4, 0.7, 1.0};
    double prob_precio15[] = {0.15, 0.45, 0.8, 1.0};
    double prob_precio2[] = {0.3, 0.7, 0.9, 1.0};

    cout << "Dias sin espacio,Latas donadas,Dias sin satisfacer,Latas perdidas" << endl;

    for (int i = 0; i < num_veces; i++)
    {
        double *probabilidades = prob_precio2;

        int dias = 30;
        int almacen = 20;
        const int ALMACEN_MAX = 200;

        int latas_perdidas_falta_stock = 0;
        int latas_donadas = 0;

        int dias_almacen_insuficiente = 0;
        int dias_sin_satisfacer = 0;

        for (int d = 0; d < dias; d++)
        {
            if (almacen + 100 > ALMACEN_MAX)
            {
                latas_donadas += almacen + 100 - ALMACEN_MAX;
                dias_almacen_insuficiente++;
                almacen = ALMACEN_MAX;
            }
            else
            {
                almacen += 100;
            }

            int demanda = genera_demanda(demandas, probabilidades);

            if (almacen < demanda)
            {
                latas_perdidas_falta_stock += demanda - almacen;
                dias_sin_satisfacer++;
                almacen = 0;
            }
            else
            {
                almacen -= demanda;
            }

            if (almacen > 125)
            {
                probabilidades = prob_precio1;
            }
            else if (almacen > 75)
            {
                probabilidades = prob_precio15;
            }
            else
            {
                probabilidades = prob_precio2;
            }
        }

        cout << dias_almacen_insuficiente << "," << latas_donadas << "," << dias_sin_satisfacer << "," << latas_perdidas_falta_stock << endl;
    }
}
