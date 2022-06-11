#include "RedSocial.h"
#include "Usuario.h"

using namespace std;

RedSocial::RedSocial(){
		/*
			Pre: Verdadero
			Post: Construye una red social vacía.
		*/
		
    this->_usuarios = *(new set<int>);
		this->_cant_amistades = 0;
		this->_popular = nullptr;
		this->_usr_id = *(new map<int, Usuario*>);
		this->_usr_alias = *(new map<string, Usuario*>);
}

const set<int> & RedSocial::usuarios() const{
		/*
			Pre: Verdadero
			(Devuelve por referencia el conjunto de identificadores (id) de todos los usuarios actualmen- te registrados)
		*/
	
    return this->_usuarios;
}

string RedSocial::obtener_alias(int id) const{
		/*
			Pre: id está en el conjunto usuarios()
			(Devuelve el alias del usuario correspondiente al identificador id)
		*/

		Usuario *usr = this->_usr_id.at(id); // O(log n)
		return usr->obtener_alias(); // O(1)
}

const set<string> & RedSocial::obtener_amigos(int id) const{
		/*
			Pre: id está en el conjunto usuarios()
			(Devuelve por referencia el conjunto de los alias de los amigos del usuario id)
		*/
    
		Usuario *usr = this->_usr_id.at(id); // O(log n)
		return usr->obtener_amigos(); // O(1)
}

int RedSocial::cantidad_amistades() const{
		/*
			Pre: Verdadero
			(Devuelve la cantidad total de relaciones de amistad actualmente en la red. Si dos usuarios A y B son amigos eso cuenta como una relación de amistad.)
		*/
  
    return this->_cant_amistades;
}

void RedSocial::registrar_usuario(string alias, int id){
		/*
			Pre: id no está en el conjunto usuarios(), alias no está asociado a ningún id, y la longitud de alias es menor o igual a 100.
			Post: El conjunto usuarios() tiene un elemento más: id; y obtener_alias(id) devuelve alias.
		*/
	
    Usuario *usr = new Usuario(id, alias);

		if (this->_popular == nullptr){
			this->_popular = usr;
		}
	
		this->_usuarios.insert(id); // O(log n)
		this->_usr_id.insert({id, usr}); // O(log n)
		this->_usr_alias.insert({alias, usr}); // O(log n)
}

void RedSocial::eliminar_usuario(int id){
		/*
			Pre: id está en el conjunto usuarios()
			Post: Se elimina al usuario id del sistema y se eliminan todas las relaciones de amistad de las que participaba.
		*/
	
		Usuario *usr = this->_usr_id.at(id); // O(log n)
		string alias = usr->obtener_alias(); // O(1)

	 	// O(n log n)
		for (set<string>::iterator itr = usr->obtener_amigos().begin(); itr != usr->obtener_amigos().end(); itr++)
  	{
			Usuario *usr_O = _usr_alias.at(*itr); // O(log n)
			int prev_amigos_O = usr_O->cantidad_amigos(); // O(1)
			usr_O->desamigar_usuario(usr); // O(log n)
			int amigos_O = usr_O->cantidad_amigos(); // O(1)
			this->_cant_amistades -= prev_amigos_O - amigos_O;
		}
		usr->desamigar_todos(); // O(n log n)
		
		// O(n log n)
		if (this->_popular->obtener_id() == id){
			this->_popular = nullptr;
			for (set<int>::iterator itr = this->_usuarios.begin(); itr != this->_usuarios.end(); itr++) // O(n)
	  	{
				Usuario *usr_ = this->_usr_id.at(*itr); // O(log n)
				if (this->_popular == nullptr){
					this->_popular = usr_;
				}
				
				if (usr_->cantidad_amigos() >= this->_popular->cantidad_amigos()) {
					this->_popular = usr_;
				}
			}
		}
		
		usr = nullptr;
		delete usr;
	
	  this->_usuarios.erase(id);
		this->_usr_id.erase(id);
		this->_usr_alias.erase(alias);

}

void RedSocial::amigar_usuarios(int id_A, int id_B){
		/*
			Pre: id_A y id_B están en el conjunto usuarios()
			Post: El conjunto obtener_amigos(id_A) tiene un elemento más: id_B y el conjunto obtener_amigos(id_B) tiene un elemento más: id_A.
		*/
		
    Usuario *usr_A = this->_usr_id.at(id_A); // O(log n)
    Usuario *usr_B = this->_usr_id.at(id_B); // O(log n)
	
		int prev_amigos_A = usr_A->cantidad_amigos();
		usr_A->amigar_usuario(usr_B); // O(log n)
		usr_B->amigar_usuario(usr_A); // O(log n)
		int amigos_A = usr_A->cantidad_amigos();
		
		this->_cant_amistades += amigos_A - prev_amigos_A;

	 	// O(n log n)
		for (set<int>::iterator itr = this->_usuarios.begin(); itr != this->_usuarios.end(); itr++)
  	{
			Usuario *usr = this->_usr_id.at(*itr); // O(log n)
			if (usr->cantidad_amigos() > this->_popular->cantidad_amigos()) {
				this->_popular = usr;
			}
		}
}

void RedSocial::desamigar_usuarios(int id_A, int id_B){
		/*
			Pre: id_A y id_B están en el conjunto usuarios() y son amigos.
			Post: El conjunto obtener_amigos(id_A) tiene un elemento menos: id_B. El conjunto obtener_amigos(id_B) tiene un elemento menos: id_A.
		*/
	
    Usuario *usr_A = this->_usr_id.at(id_A); // O(log n)
    Usuario *usr_B = this->_usr_id.at(id_B); // O(log n)
	
		int prev_amigos_A = usr_A->cantidad_amigos(); // O(1)
		usr_A->desamigar_usuario(usr_B); // O(log n)
		usr_B->desamigar_usuario(usr_A); // O(log n)
		int amigos_A = usr_A->cantidad_amigos(); // O(1)
		this->_cant_amistades -= prev_amigos_A - amigos_A;

		// O(n log n)
		for (set<int>::iterator itr = this->_usuarios.begin(); itr != this->_usuarios.end(); itr++)
  	{
			Usuario *usr = this->_usr_id.at(*itr); // O(log n)
			if (usr->cantidad_amigos() > this->_popular->cantidad_amigos()) {
				this->_popular = usr;
			}
		}
}

int RedSocial::obtener_id(string alias) const{
		/*
			Pre: Hay un id en usuarios() que tiene asociado el alias alias. 
			Post: Devuelve el id de usuarios() que tiene asociado el alias alias.
		*/
	
		Usuario *usr = this->_usr_alias.at(alias); // O(log n)
    return usr->obtener_id(); // O(1)
}

const set<string> & RedSocial::amigos_del_usuario_mas_popular() const{
    /*
			Pre: cantidad_amistades() es mayor a cero.
			Post: Devuelve por referencia el conjunto de los alias de los amigos del usuario más popular (aquel que tenga la mayor cantidad de amigos de la red). Si hay más de un usuario más popular, devuelve los amigos correspondientes a cualquiera de ellos.
		*/
	
    return this->_popular->obtener_amigos();  // O(1)
}