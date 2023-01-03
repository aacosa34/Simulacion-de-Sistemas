#include <iostream>

using namespace std;

double t, tinic, tfin;
double dt, a, b, c;

/* Vectores de estado */
double *estado, *oldestado;

int numeq;
void (*oneStep)(double *, double *, double, double);

void derivacion(double *est, double *f, double tt)
// espec�fico para el modelo considerado
// con inmunidad
// {
//     f[0] = a * est[0] * est[1] - b * est[0];
//     f[1] = -a * est[0] * est[1];
//     f[2] = b * est[0];
// }
// sin inmunidad
{
    f[0] = a * est[0] * est[1] - b * est[0];
    f[1] = -a * est[0] * est[1] + est[2] * c;
    f[2] = b * est[0] - est[2] * c;
}

void oneStepRungeKutta(double *inp, double *out, double tt, double hh)
{
    double time, *f, incr, **k;

    f = new double[numeq];
    k = new double *[numeq];
    for (int i = 0; i < numeq; i++)
    {
        k[i] = new double[4];
    }

    for (int i = 0; i < numeq; i++)
        out[i] = inp[i];
    time = tt;
    for (int j = 0; j < 4; j++)
    {
        derivacion(out, f, time);
        for (int i = 0; i < numeq; i++)
            k[i][j] = f[i];
        double incr;
        if (j < 2)
            incr = hh / 2;
        else
            incr = hh;
        time = tt + incr;
        for (int i = 0; i < numeq; i++)
            out[i] = inp[i] + k[i][j] * incr;
    }
    for (int i = 0; i < numeq; i++)
        out[i] = inp[i] + hh / 6 * (k[i][0] + 2 * k[i][1] + 2 * k[i][2] + k[i][3]);
}

void oneStepEuler(double *inp, double *out, double tt, double hh)
{
    double *f;

    f = new double[numeq];

    derivacion(inp, f, tt);
    for (int i = 0; i < numeq; i++)
        out[i] = inp[i] + hh * f[i];
}

void fijarParametros(char *argv[])
{
    oneStep = oneStepEuler;
    estado = new double[numeq];
    numeq = 3;
    tinic = 0.0;
    tfin = atof(argv[1]);
    a = atof(argv[2]);
    b = atof(argv[3]);
    c = atof(argv[4]);
    dt = atof(argv[5]);
    estado[0] = atof(argv[6]);
    estado[1] = atof(argv[7]);
    estado[2] = atof(argv[8]);
}

void salida()
{
    cout << t << "," << estado[0] << "," << estado[1] << "," << estado[2] << endl;
}

void integracion()
{
    do
    {
        salida();
        oldestado = estado;
        oneStep(oldestado, estado, t, dt); // sustituir por one-step-runge-kutta o por one-step-euler
        t += dt;
    } while (t < tfin);
}

int main(int argc, char *argv[])
{
    if (argc != 9)
    {
        cerr << "Usage: " << argv[0] << " tfin a b c dt I S R" << endl;
        exit(1);
    }
    fijarParametros(argv);
    t = tinic;

    // Cabecera del CSV
    cout << "t,I,S,R" << endl;
    integracion();
}