#include <iostream>
#include "Stack.h"
#include <stdlib.h>
#include "IzrazValidator.h"
#include "Sabirator.h"
#include "PostFixRacunator.h"
#include "PreFixRacunator.h"

int main(void)
{
	IzrazValidator validator("(1 + ( 2 + [3 + 3]  + 1 + { 2 + 2 }))");

	if (validator.validate())
	{
		std::cout << "Ipravno\n";
	}
	else
	{
		std::cout << "Ne valja\n";
	}

	PostFixRacunator racunator_postfix("10 6 + 2 - 7 / 10 *");

	std::cout << racunator_postfix.calculate_postfix() << '\n';

	PreFixRacunator racunator_prefix("* / - +  10 6 2 7 10");

	std::cout << racunator_prefix.calculate_prefix() << '\n';

	Sabirator sab("482523", "235345435534");
		
	sab.add();

	sab.show_rez();

	return 0;
}