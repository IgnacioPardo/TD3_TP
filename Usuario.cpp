	#include "Usuario.h"

using namespace std;

Usuario::Usuario(int id_, string alias_){
		this->_id = id_;
		this->_alias = alias_;
		this->_amigos = *(new set<Usuario*>);
		this->_alias_amigos = *(new set<string>);
		this->_cantidad_amigos = 0;
}


string Usuario::obtener_alias() const{
	//Post: Devuelve el alias del Usuario
	return this->_alias;
}

int Usuario::obtener_id() const{
	//Post: Devuelve el id del Usuario
	return this->_id;
}


void Usuario::amigar_usuario(Usuario *usr){
		//Post: El conjunto this->_amigos tiene un elemento mas: usr
		// 			El conjunto this->_alias_amigos tiene un elemento mas: usr._alias
		//			this->_cantidad_amigos = |this->_amigos| = |this->_alias_amigos|
		
		this->_cantidad_amigos += 1 - this->_amigos.count(usr); //O(log n)
		this->_amigos.insert(usr); //O(log n)
	  this->_alias_amigos.insert(usr->obtener_alias()); //O(log n)
}

void Usuario::desamigar_usuario(Usuario *usr){
		//Post: El conjunto this->_amigos tiene un elemento menos: usr
		// 			El conjunto this->_amigos_amigos tiene un elemento menos: usr._alias
		//			this->_cantidad_amigos = |this->_amigos| = |this->_alias_amigos|
		
		this->_cantidad_amigos -= this->_amigos.count(usr); //O(log n)
		this->_amigos.erase(usr); //O(log n)
		this->_alias_amigos.erase(usr->obtener_alias()); //O(log n)
}

void Usuario::desamigar_todos(){
		//Post: El conjunto this->_amigos es el conjunto vacio.
		// 			El conjunto this->_amigos_amigos es el conjunto vacio.
		//			this->_cantidad_amigos = |this->_amigos| = |this->_alias_amigos| = 0

		this->_cantidad_amigos = 0;
		this->_amigos = *(new set<Usuario*>); //O(log n)
		this->_alias_amigos = *(new set<string>); //O(log n)
}

const set<string> & Usuario::obtener_amigos() const{
	//Post: Devuelve por referencia el conjunto de los alias de los amigos
	
	return this->_alias_amigos;
}

int Usuario::cantidad_amigos() const{
	// Devuelve la cantidad de elementos en los conjuntos amigos y alias_amigos.
	
	return this->_cantidad_amigos;
}