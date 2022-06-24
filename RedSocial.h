#ifndef __REDSOCIAL_H__
#define __REDSOCIAL_H__

#include <string>
#include <set>
#include <map>
//#include "Usuario.h"

/*

		No existen dos usuarios con el mismo id ni el mismo alias.
		La cantidad de amistades es igual a la mitad de la suma de todas las cantidades de amigos de todos los usuarios de la Red Social.
		Para todo id del conjunto usuarios, existe un unico par key/value en el map _usr_id donde la key es dicho id, y su value es un puntero a un usuario con ese id, 
		y a su vez existe un unico par key/value en el map _usr_alias donde la key es el alias del usuario en el map _usr_id bajo dicho id, y su value es un puntero a un usuario con ese id y ese alias.
		Si la Red Social tiene usuarios registados, el usuario mas popular va a ser quien tenga mayor cantitad de amigos, de no tener, se indefine.
		
		Rep(rs : RedSocial) ≡ 
						| rs._usuarios | = | rs._usr_id | = | rs._usr_alias | &&
						values(rs._usr_id) = values(rs._usr_alias) && // mapEqualValues(rs._usr_id, rs._usr_alias) //
						((∀u: Usuario) &u ∈ values(rs._usr_id) =>
							((∃!!i: int) i ∈ rs._usuarios => i = u.id) && 
							((∃!!j: int) j ∈ keys(rs._usr_id) => rs._usr_id[j] = u => j = u.id) && 
							((∃!!k: string) k ∈ keys(rs._usr_alias) => rs._usr_alias[k] = u)) &&
						rs._cant_amistades = | (∑ (i: int) ∈ rs._usuarios (rs._usr_id[i]._cantidad_amigos)) | / 2 && 
						((| rs._usuarios | > 0 =>
							rs._popular._id ∈ rs._usuarios &&
							((∀i: int) i ∈ rs._usuarios => i._cantidad_amigos <= rs._popular._cantidad_amigos))
							|| rs._popular = nullptr)

		mapEqualValues(map<T, T_> a, map<T, T_> b) ≡ ((∀k: T) ∈ keys(a) => (∃!! k_: T) k_ ∈ keys(b) a[k] = b[k_]) && ((∀k: T) ∈ keys(b) => (∃!! k_: T) ∈ keys(a) a[k] = b[k_])

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

		class Usuario{
		  public:
				Usuario(int id_, std::string alias_);
		    std::string obtener_alias() const; // O(1)
				int obtener_id() const; // O(1)

				int cantidad_amigos() const; // O(1);
				const std::set<std::string> & obtener_amigos() const; // O(1)

				void amigar_usuario(Usuario *usr); // O(log n)
		    void desamigar_usuario(Usuario *usr); // O(log n)
				void desamigar_todos(); //O(log n)

			private:
				int _id, _cantidad_amigos;
		    std::string _alias;
		    std::set<Usuario*> _amigos;
		    std::set<std::string> _alias_amigos;    
		};
		
		int _cant_amistades;
		Usuario *_popular;
		std::set<int> _usuarios;
		std::map<int, Usuario*> _usr_id;
		std::map<std::string, Usuario*> _usr_alias;
};

#endif