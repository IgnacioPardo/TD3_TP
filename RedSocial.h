#ifndef __REDSOCIAL_H__
#define __REDSOCIAL_H__

#include <string>
#include <set>
#include <map>
#include "Usuario.h"

/*
	No existen dos usuarios con el mismo id ni con el mismo alias
	La cantidad de amistades es la cantidad de elementos de la diferencia simetrica entre los conjuntos de amigos de todos los usuarios"
	
	Rep(rs : RedSocial) ≡ (∀ (i: int) ∈ rs._usuarios => 
							∄ (j: int) ∈ rs._usuarios i != j / rs._usr_id[i] == rs._usr_id[j] &&
							∄ (j: int) ∈ rs._usuarios i != j / rs._usr_alias[rs._usr_id[i]._alias] == rs._usr_alias[rs._usr_id[j]._alias]) &&
							rs._cant_amistades = |(⊖ (i: int) ∈ rs._usuarios (rs._usr_id[i]._amigos))|
*/

class RedSocial{
  public:
    RedSocial();

    const std::set<int> & usuarios() const; // O(1)
    std::string obtener_alias(int id) const; // O(log n)
    const std::set<std::string> & obtener_amigos(int id) const; // O(log n)
    int cantidad_amistades() const; // O(1)

    void registrar_usuario(std::string alias, int id); // O(log n)
    void eliminar_usuario(int id); // O(n log n)
    void amigar_usuarios(int id_A, int id_B); // O(n log n)
    void desamigar_usuarios(int id_A, int id_B); // O(n log n)
    
    int obtener_id(std::string alias) const; // O(log n)
    const std::set<std::string> & amigos_del_usuario_mas_popular() const; // O(1)

  private:
		int _cant_amistades;
		Usuario *_popular;
		std::set<int> _usuarios;
		std::map<int, Usuario*> _usr_id;
		std::map<std::string, Usuario*> _usr_alias;
};

#endif