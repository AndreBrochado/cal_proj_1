#include "App.h"
#include "Exceptions.h"



void ReadData(App &a , string filename)
{
	ifstream in;
    string file = filename+".txt";
	in.open(file.c_str(), ios::in);
	if (in.good())
	{
		while (in.good()){
					string dummy;
					string name, adress, licensePlate, brand;
					int capacity;

					getline(in, dummy, '/');

					if( dummy == "-"){
						getline(in, name, '_');
						cout << name << endl;
						getline(in, adress, '\n');
						cout << adress << endl;


					}

					if( dummy == "*"){
						getline(in, dummy, '_');
						capacity = atoi(dummy.c_str());
						cout << capacity << endl;
						getline(in, licensePlate, '_');
						cout << licensePlate<< endl;
						getline(in, brand, '\n');
						cout << brand<< endl;
					}
/*
					if (!in.eof()){
						in.ignore(1000, '\n');
					}
*/
					if (in.eof()){
						return;
					}

		}
	}
	if (in.fail())
				throw FileReadingError();


	/*
		if (in.peek() != std::ifstream::traits_type::eof())
		{
			while (in.good())
			{
				char dummy;
				string nome, descricao;
				float precoBase, duracao;

				getline(in, nome, '_');
				getline(in, descricao, '_');
				in >> precoBase >> dummy >> duracao;*/

/*
				if (!in.eof())
					in.ignore(1000, '\n');

				f.addServico(nome, descricao, precoBase, duracao);
			}
			*/


		in.close();
	}

void App::AddUser(string name, string adress){
	User* u1 = new User(name,adress);
	users.push_back(u1);
};



void App::AddCar(User u, int Capacity, string licensePlate, string brand){
	Car* c1 = new Car(Capacity,licensePlate,brand);
	for (unsigned i = 0; i < users.size(); i++){
		if(u.returnID() == users[i]->returnID()){
			users[i]->addCar(*c1);
			cout << "added";
		}
		else cout << "not";
	}
};
