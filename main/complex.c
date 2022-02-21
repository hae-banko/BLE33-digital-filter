/*----------------------------------
Modul: Komplexe Zahl
Autor: Irvan Fikardi

Datastruktur einer Komplexe Zahl mit 
den entsprechenden Funktionen fuer
Rechnungen mit den komplexen Zahl 
----------------------------------*/

#include <stdio.h>
#include <math.h>

//besitzt Datenstruktur cplx für Komplexe Zahlen
#include "complex.h"

//reele Zahlen
double real(cplx z){
    return z.r;
}

//imaginäre Zahlen
double imag(cplx z){
    return z.i;
}

//Betrag von Imag. Zahlen
double betrag(cplx z){
    return sqrt(z.r*z.r + z.i*z.i);
}

//Phase einer komplexe Zahlen Berechnen
double phase (cplx z){
    double phi; 
    if (z.r == 0.0)
    {   
        if(z.i == 0.0) {
                phi = 0.0;
            }
        else {
            if(z.i > 0) {
                phi = M_PI / 2.0;
            } 
            else {
                phi = -M_PI / 2.0;
            }
        }
    }

    else {
        phi = atan2(z.i, z.r); 
    }

    return(phi);
}

//Zahlen zu komplexe Zahlen konvertieren
cplx make_cplx(double r, double i)
{
    cplx z;

    z.r = r;
    z.i = i;
    return z;
}

//Komplexe Zahlen kartesisch darstellen 
void c_print_kartesisch(cplx z){
    printf("(%.4lf|%.4lf) ",z.r,z.i);
}

//Komplexe Zahlen polar darstellen
void c_print_polar(cplx z){
    printf("Modulus: %4.lf | Winkel: %.2lf rad", betrag(z), (phase(z)));
}

//Komplexe Zahlen polar mit Grad darstellen 
void c_print_polar_grad(cplx z)
{
    printf("Modulus:%.4lf | Winkel: %.2lf Grad", 
    betrag(z), 
    (phase(z)/M_PI*180.0)
    );
}

//Komplexe Zahlen eingeben 
cplx c_input_kartesisch(void){
    cplx z; 

    printf("Realteil: ");
    scanf("%lf", &z.r);
    printf("Imaginärteil: ");
    scanf("%lf", &z.i);
    return z;
}

//Komplexe Zahlen polar eingeben
cplx c_input_polar(void){
    cplx z;
    double r, phi_grad, phi_rad;

    printf("Betrag: ");
    scanf("%lf", &r);
    printf("Winkel in Grad: ");
    scanf("%lf", &phi_grad);

    phi_rad = phi_grad/180.0 * M_PI;
    z.r = r * cos(phi_rad);
    z.i = r * sin(phi_rad);
    return z;
}

//Addition zweier komplexe Zahlen
cplx c_add(cplx z1, cplx z2){
    cplx z; 
    z.r = z1.r + z2.r;
    z.i = z1.i + z2.i;
    return z;
}

//Subtraktion zweier komplexe Zahlen
cplx c_sub(cplx z1, cplx z2){
    cplx z;
    z.r = z1.r - z2.r;
    z.i = z1.i - z2.i;
    return z;
}

//Multiplikation zweier komplexe Zahlen
cplx c_mult(cplx z1, cplx z2){
    cplx z;
    z.r = z1.r * z2.r;
    z.i = z1.i * z2.i;
    return z;
}

//Invers von einer komplexen Zahlen
cplx c_invers(cplx z){
    double x;
    cplx z1;

    x = z.r * z.r + z.i * z.i;
    z1 = make_cplx(z.r/x, -z.i/x);
    return z1;
}

//Division von zweier komplexen Zahlen
cplx c_div(cplx z1, cplx z2){
    return c_mult(z1, c_invers(z2));
}

//exponentiell
cplx c_exp(cplx z){
    cplx z1;
    z1.r = exp(z.r) * cos(z.i);
    z1.i = exp(z.r) * sin(z.i);
    return z1;
}

//Wurzel von einer kompl. Zahlen
cplx c_sqrt(cplx z){
    cplx z1;
    z1.r = sqrt(betrag(z)) * cos(phase(z)/2.0);
}