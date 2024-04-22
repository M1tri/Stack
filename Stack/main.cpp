#include <iostream>
#include "Stack.h"
#include <stdlib.h>
#include "IzrazValidator.h"
#include "Sabirator.h"
#include "PostFixRacunator.h"
#include "PreFixRacunator.h"
#include "String.h"
#include "PostFixKonvertator.h"
#include "StringReader.h"


int main(void)
{
	String izraz = "6 / 2 * (1 + 2)";
	
	IzrazValidator validator(izraz);

	if (validator.validate())
	{
		std::cout << "Ipravno sa stanovista zatvaranja i otvaranja zagrada\n";
	}
	else
	{
		std::cout << "Izraz nije valida!\n";
		return -1;
	}

	PostFixKonvertator konvertator(izraz);

	konvertator.convert();

	std::cout << "Racunjanje:\n";

	PostFixRacunator racunator(konvertator.get_expresion());

	try
	{
		int rez = racunator.calculate_postfix();
		std::cout << izraz << " = ";
		std::cout << rez << '\n';
	}
	catch (...)
	{
		std::cout << "Greska pri racunjanju, proverite da li su svi operandi ispravno navedeni!\n";
		return -1;
	}

	std::cout << "---------------\n";


	PreFixRacunator calc("**+ 4 / 3 5 - 9 3 4");

	std::cout << calc.calculate_prefix() << '\n';

	String num1 = "482523";
	String num2 = "235345435534";

	Sabirator sab(num1, num2);

	sab.add();

	std::cout << num1 << " + " << num2 << " = ";
	sab.show_rez();
	std::cout << '\n';


	StringReader str("nesto");

	std::cout << str;

	str.push_back('1');
	str.push_back('2');
	str.push_back('3');
	str.push_back('4');
	str.push_back('5');
	

	std::cout << str;


	str.push_back('6');
	str.push_back('7');
	str.push_back('8');
	str.push_back('9');
	str.push_back('1');
	str.push_back('0');
	str.push_back('1');
	str.push_back('1');


	std::cout << str;


	return 0;
}