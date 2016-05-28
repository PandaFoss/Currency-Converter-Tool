#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>

char a[44]="ttps://www.google.com/finance/converter?a=";
char b[7]="&from=";
char c[5]="&to=";

char concatenarLink (char *pLink, char *a, char *cantidad, char *b, char *monedaOrigen, char *c, char *monedaDestino);
void cURLfuncion(FILE *pDatos, char *pLink);
char *crearArrayBusca (FILE *pArchivo, char *busca);
char *resultadoEncontrado (char *busca, char *texto, int posIni, int posFin);
void helpMsg (void);
void infoMsg (void);
void badArgs (void);
