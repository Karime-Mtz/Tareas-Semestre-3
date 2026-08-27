/*
 * funciones.h
 *
 *  Created on: 08/27/2026
 *      Author: Karime M
 */

#ifndef RECURSION_H_
#define RECURSION_H_


class Funciones{

    public:

        int sumaIterativa(int n){
            int suma = 0;
            for (int i = 1; i <= n; i++){
                suma += i;
            }
            return suma;
        }

        int sumaRecursiva(int n){
            if (n == 0){
                return 0;
            }
            return n + sumaRecursiva (n-1);
        }

        int sumaDirecta(int n){
            return (n*(n+1))/2;
        }

};


#endif