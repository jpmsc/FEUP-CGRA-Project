
#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "LightingScene.h"
#include "TPinterface.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(new LightingScene());
		app.setInterface(new TPinterface());
		//app.setInterface(new CGFinterface());
		
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Erro: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}

	return 0;
}