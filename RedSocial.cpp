#include "RedSocial.h"
#include "Usuario.h"

using namespace std;

RedSocial::RedSocial(){
    this->_usuarios = *(new set<int>);
		this->_cant_amistades = 0;
		this->_popular = nullptr;
}

const set<int> & RedSocial::usuarios() const{
	
    return this->_usuarios;
}

string RedSocial::obtener_alias(int id) const{

		Usuario *usr = this->_usr_id.at(id); // O(log n)
	
		return usr->obtener_alias(); // O(1)
}

const set<string> & RedSocial::obtener_amigos(int id) const{
	
    Usuario *usr = this->_usr_id.at(id); // O(log n)
    
		return usr->obtener_amigos(); // O(1)
}

int RedSocial::cantidad_amistades() const{
  
    return this->_cant_amistades;
}

void RedSocial::registrar_usuario(string alias, int id){
    Usuario *usr = new Usuario(id, alias);

		if (this->_popular == nullptr){
			this->_popular = usr;
		}
	
		this->_usuarios.insert(id); // O(log n)
		this->_usr_id.insert({id, usr}); // O(log n)
		this->_usr_alias.insert({alias, usr}); // O(log n)
}

void RedSocial::eliminar_usuario(int id){
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
		Usuario *usr = this->_usr_alias.at(alias); // O(log n)
	
    return usr->obtener_id(); // O(1)
}

const set<string> & RedSocial::amigos_del_usuario_mas_popular() const{
    
    return this->_popular->obtener_amigos();  // O(1)
}