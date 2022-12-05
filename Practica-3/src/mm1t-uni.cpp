#include "mm1t-uni.h"

bool compare(const suc &s1, const suc &s2)
{
  return s1.tiempo < s2.tiempo;
}

/* Inserta de forma ordenada un elemento en la lista de sucesos */
void insertar_lsuc(suc n)
{
  lsuc.push_back(n);

  // Mantener ordenada la lista por el tiempo de los sucesos
  lsuc.sort(compare);
}

/* Procedimiento inicializacion */
void inicializacion()
{
  int i;

  // inicializacion de variables de estado
  reloj = 0.0;
  operario_libre = true;
  maquinas_libres = num_maquinas;
  encola_lleg = 0;
  while (!cola_llegadas.empty())
  {
    cola_llegadas.pop_front();
  }
  encola_sal = 0;
  while (!cola_salidas.empty())
  {
    cola_salidas.pop_front();
  }
  tdus_lleg = 0.0;
  tdus_sal = 0.0;

  // inicializacion de contadores estadisticos
  acum_lleg = 0.0;
  acum_sal = 0.0;
  acum_estancia = 0.0;
  acum_ocio = 0.0;
  total_procesados = 0;
  comienzo_ocio = reloj;

  // inicializacion de la lista de sucesos
  while (!lsuc.empty())
  {
    lsuc.pop_front();
  }
  nodo.tllego = 0;
  nodo.suceso = SUCESO_FIN_SIMULACION;
  nodo.tiempo = reloj + tparada;
  insertar_lsuc(nodo);
  nodo.suceso = SUCESO_LLEGADA_TRABAJO;
  nodo.tiempo = reloj + genera_trabajo(tllegada);
  insertar_lsuc(nodo);

  parar = false;
}

/* Procedimiento temporizacion */
void temporizacion()
{
  nodo = lsuc.front();
  lsuc.pop_front();
  reloj = nodo.tiempo;
}

/* Procedimiento suceso */
void suceso()
{
  switch (nodo.suceso)
  {
  case SUCESO_LLEGADA_TRABAJO:
    llegada_trabajo();
    break;
  case SUCESO_FIN_CARGA:
    fin_carga();
    break;
  case SUCESO_FIN_DESCARGA:
    fin_descarga();
    break;
  case SUCESO_FIN_PROCESAMIENTO:
    fin_procesamiento();
    break;
  case SUCESO_FIN_SIMULACION:
    fin_simulacion();
    break;
  }
}

/* Peocedimiento llegada de trabajo */
void llegada_trabajo()
{
  nodo.suceso = SUCESO_LLEGADA_TRABAJO;
  nodo.tiempo = reloj + genera_trabajo(tllegada);
  nodo.tllego = 0;
  insertar_lsuc(nodo); // programa la proxima llegada
  if (operario_libre && maquinas_libres > 0)
  {
    nodo.suceso = SUCESO_FIN_CARGA;
    nodo.tiempo = reloj + genera_carga(tcarga);
    nodo.tllego = reloj;
    insertar_lsuc(nodo);
    operario_libre = false;
    maquinas_libres--;
    acum_ocio += reloj - comienzo_ocio;
  }
  else
  {
    acum_lleg += (reloj - tdus_lleg) * encola_lleg;
    tdus_lleg = reloj;
    encola_lleg++;
    cola_llegadas.push_back(reloj);
  }
}

/* Procedimiento fin de carga */
void fin_carga()
{
  float cuandollegue;

  nodo.suceso = SUCESO_FIN_PROCESAMIENTO;
  nodo.tiempo = reloj + genera_procesamiento(tproceso);
  // nodo.tllego se deja como esta, se hereda del suceso actual
  insertar_lsuc(nodo);
  if (encola_sal > 0)
  {
    acum_sal += (reloj - tdus_sal) * encola_sal;
    tdus_sal = reloj;
    encola_sal--;
    cuandollegue = cola_salidas.front();
    cola_salidas.pop_front();
    nodo.suceso = SUCESO_FIN_DESCARGA;
    nodo.tiempo = reloj + genera_descarga(tdescarga);
    nodo.tllego = cuandollegue;
    insertar_lsuc(nodo);
  }
  else if (encola_lleg > 0 && maquinas_libres > 0)
  {
    acum_lleg += (reloj - tdus_lleg) * encola_lleg;
    tdus_lleg = reloj;
    encola_lleg--;
    maquinas_libres--;
    cuandollegue = cola_llegadas.front();
    cola_llegadas.pop_front();
    nodo.suceso = SUCESO_FIN_CARGA;
    nodo.tiempo = reloj + genera_carga(tcarga);
    nodo.tllego = cuandollegue;
    insertar_lsuc(nodo);
  }
  else
  {
    operario_libre = true;
    comienzo_ocio = reloj;
  }
}

/* Procedimiento fin de procesamiento */
void fin_procesamiento()
{
  if (operario_libre)
  {
    nodo.suceso = SUCESO_FIN_DESCARGA;
    nodo.tiempo = reloj + genera_descarga(tdescarga);
    // nodo.tllego se deja como esta, se hereda del suceso actual
    insertar_lsuc(nodo);
    operario_libre = false;
    acum_ocio += reloj - comienzo_ocio;
  }
  else
  {
    acum_sal += (reloj - tdus_sal) * encola_sal;
    tdus_sal = reloj;
    encola_sal++;
    cola_salidas.push_back(nodo.tllego);
  }
}

/* Procedimiento fin de descarga */
void fin_descarga()
{
  float cuandollegue;

  maquinas_libres++;
  total_procesados++;
  acum_estancia += reloj - nodo.tllego;
  if (encola_sal > 0)
  {
    acum_sal += (reloj - tdus_sal) * encola_sal;
    tdus_sal = reloj;
    encola_sal--;
    cuandollegue = cola_salidas.front();
    cola_salidas.pop_front();
    nodo.suceso = SUCESO_FIN_DESCARGA;
    nodo.tiempo = reloj + genera_descarga(tdescarga);
    nodo.tllego = cuandollegue;
    insertar_lsuc(nodo);
  }
  else if (encola_lleg > 0)
  {
    acum_lleg += (reloj - tdus_lleg) * encola_lleg;
    tdus_lleg = reloj;
    encola_lleg--;
    maquinas_libres--;
    cuandollegue = cola_llegadas.front();
    cola_llegadas.pop_front();
    nodo.suceso = SUCESO_FIN_CARGA;
    nodo.tiempo = reloj + genera_carga(tcarga);
    nodo.tllego = cuandollegue;
    insertar_lsuc(nodo);
  }
  else
  {
    operario_libre = true;
    comienzo_ocio = reloj;
  }
}

/* Procedimiento fin de simulacion */
void fin_simulacion()
{
  int i;

  parar = true;
  acum_lleg += (reloj - tdus_lleg) * encola_lleg;
  acum_sal += (reloj - tdus_sal) * encola_sal;
  if (operario_libre)
    acum_ocio += reloj - comienzo_ocio;
  // printf("\nNumero de trabajos esperando ser cargados = %f",acum_lleg/reloj);
  informe[cont_simu][0] = acum_lleg / reloj;
  // printf("\nNumero de trabajos esperando ser descargados = %f",acum_sal/reloj);
  informe[cont_simu][1] = acum_sal / reloj;
  // printf("\nTotal de trabajos procesados= %f",total_procesados);
  informe[cont_simu][2] = total_procesados;
  // printf("\nTiempo de estancia de los trabajos = %f",acum_estancia/total_procesados);
  informe[cont_simu][3] = acum_estancia / total_procesados;
  // printf("\nPorcentaje de tiempo de ocio del operario = %f",acum_ocio*100/reloj);
  informe[cont_simu][4] = acum_ocio * 100 / reloj;
}

/* El generador de informes se encarga de calcular la media y desviacion tipica de los valores obtenidos */
void generador_informes(int simulaciones)
{
  float media[5], dt[5];
  int i, j;

  for (j = 0; j < 5; j++)
  {
    media[j] = 0;
    for (i = 0; i < simulaciones; i++)
      media[j] += informe[i][j];
    media[j] /= simulaciones;

    dt[j] = 0;
    for (i = 0; i < simulaciones; i++)
      dt[j] += informe[i][j] * informe[i][j];
    dt[j] = sqrt((dt[j] - simulaciones * media[j] * media[j]) / (simulaciones - 1.0));
  }

  printf("\n\nINFORME ->");
  printf("\n\nNumero de trabajos esperando ser cargados: media(%f), dt(%f)", media[0], dt[0]);
  printf("\nNumero de trabajos esperando ser descargados: media(%f), dt(%f)", media[1], dt[1]);
  printf("\nNumero de trabajos procesados: media(%f), dt(%f)", media[2], dt[2]);
  printf("\nTiempo de estancia de los trabajos: media(%f), dt(%f)", media[3], dt[3]);
  printf("\nPorcentaje de tiempo de ocio del operario: media(%f), dt(%f)", media[4], dt[4]);
  printf("\n\n");
}

/* Generadores de datos */
// Generador de tiempos entre llegadas de trabajos
float genera_trabajo(float tllegada)
{
  return generador_uniforme(tllegada);
}

// Generador de tiempos de carga
float genera_carga(float tcarga)
{
  return generador_uniforme(tcarga);
}

// Generador de tiempos de descarga
float genera_descarga(float tdescarga)
{
  return generador_uniforme(tdescarga);
}

// Generador de tiempos de procesamiento
float genera_procesamiento(float tproceso)
{
  return generador_uniforme(tproceso);
}

float generador_uniforme(float media)
{
  float u;
  u = (float)random();
  u = (float)(u / (RAND_MAX + 1.0));
  // sería -> min + (max - min) * u
  // Para calcular el maximo y el minimo de 'media'
  // su min = 0 y su max = 2 * media.
  return 2 * media * u;
}

/* Programa principal */
int main(int argc, char *argv[])
{
  int i, simulaciones;

  if (argc != 2)
  {
    printf("\n\nFormato Argumentos -> <numero_simulaciones>\n\n");
    exit(1);
  }

  sscanf(argv[1], "%d", &simulaciones);

  informe = (float **)malloc(simulaciones * sizeof(float *));
  for (i = 0; i < simulaciones; i++)
    informe[i] = (float *)malloc(5 * sizeof(float));

  srandom(time(NULL));
  // srandom(123456);

  for (cont_simu = 0; cont_simu < simulaciones; cont_simu++)
  {
    // printf("\nSimulacion %d ...", cont_simu);
    inicializacion();
    while (parar == false)
    {
      temporizacion();
      suceso();
    }
  }
  generador_informes(simulaciones);

  for (i = 0; i < simulaciones; i++)
    free(informe[i]);
  free(informe);
}
