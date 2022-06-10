#include "RedSocial.h"
#include <iostream>
#include <set>
#include <string>

using namespace std;

void imprimir_set(set<string> s){
    for (string e: s)
        cout << e << " ";
    cout << endl;
}

int main(){
    // Usar main para hacer pruebas
    // No entregar.

    RedSocial rs;

    rs.registrar_usuario("agus", 5);
    rs.registrar_usuario("gerva", 4);
    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("vir", 2);
    rs.registrar_usuario("vivi", 1);

    rs.amigar_usuarios(1,2);
    rs.amigar_usuarios(1,3);
    rs.amigar_usuarios(4,5);

    rs.eliminar_usuario(1);

    imprimir_set(rs.obtener_amigos(2));
}