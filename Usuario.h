#ifndef __USUARIO_H__
#define __USUARIO_H__

#include <string>
#include <set>

/*

	La cantidad de amigos es igual a la cantidad de elementos en el conjunto amigos, y a su vez es igual a la cantidad de alias en el conjunto alias_amigos.
	Un Usuario no puede tenerse de amistad a si mismo, por lo tanto su alias no pertenece al conjunto alias_amigos y si mismo no pertenece al conjunto amigos.
	
	Rep(u : Usuario) ≡ u._cantidad_amigos = |u._cantidad_amigos| && *u ∉ u._amigos && u._alias ∉ u._alias_amigos

*/

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

#endif