#include "Helper.h"
#include "User.h"

class Group{
	Car c;
	vector <User> users;
	//aqui vai a rota, e se calhar um tupplo destino partida!?!?
public:
	Group(Car c);// aqui provavelmente era melhor inicializar com a rota
	void addUser(User u);
	void changeCar(Car c);
	void changeRoute(); //n implementado
	vector<User> returnUsers();
	Car returnCar();
};



