// Project FLIE-Fuzzy Logic Inference Engine - Jo�o Alberto Fabro - out/1996

// File flie.cc

#include <stdlib.h> // Random!
#include <stdio.h> // Random!
#define DOS
#include "rightMotor.h"

/*Deve-se definir um sistema de controle que ir� conter as regras.*/
fuzzy_control fuzzycontrolD;

/*No programa principal � necess�rio instanciar as vari�veis para conter
todos os conjuntos fuzzy e tamb�m defini-los.*/

trapezoid_category cat1[15];



/*Deve-se definir as vari�veis lingu�sticas que ir�o conter os conjuntos fuzzy*/

linguisticvariable sens_front, sens_right, sens_left, lingRightMotor;



/*Deve-se definir as regras de infer�ncia que ir�o reger o comportamento do
sistema de controle.� necess�rio instanci�-los.*/

//TODO
rule infruleD[99];

rightMotor::rightMotor(){
	mainD();
}

rightMotor::~rightMotor(){

}

void rightMotor::mainD()
{
        int i;



/*deve-se definir vari�veis que ir�o conter as entradas e sa�das(defuzificadas)
do sistema submetidas ao controle.*/

float SumError, ControlOutput;


/* Define-se os conjuntos fuzzy para a vari�vel lingu�stica Error*/

	/*
	 MP = Muito Perto
	 P  = Perto
	 M  = M�dio
	 L  = Longe
	 ML = Muito Longe
	 */


	cat1[0].setname("M");
	cat1[0].setrange(0, 1000);
	cat1[0].setval(0, 0, 500, 1000);

	cat1[1].setname("P");
	cat1[1].setrange(500, 1400);
	cat1[1].setval(500, 1000, 1200, 1400);

	cat1[2].setname("MP");
	cat1[2].setrange(1400, 2000);
	cat1[2].setval(1400, 1500, 2000, 2000);



	/*Define-se a Vari�vel lingu�stica Error*/

	sens_right.setname("Sensores da direita");

	sens_right.includecategory(&cat1[0]);

	sens_right.includecategory(&cat1[1]);

	sens_right.includecategory(&cat1[2]);



	cat1[3].setname("M");
	cat1[3].setrange(0, 1000);
	cat1[3].setval(0, 0, 500, 1000);

	cat1[4].setname("P");
	cat1[4].setrange(500, 1400);
	cat1[4].setval(500, 1000, 1200, 1400);

	cat1[5].setname("MP");
	cat1[5].setrange(1400, 2000);
	cat1[5].setval(1400, 1500, 2000, 2000);


	/*Define-se a Vari�vel lingu�stica Error*/

	sens_left.setname("Sensores da esquerda");

	sens_left.includecategory(&cat1[3]);

	sens_left.includecategory(&cat1[4]);

	sens_left.includecategory(&cat1[5]);


	/*Define-se os conjuntos fuzzy para a vari�vel lingu�stica Control*/

	cat1[6].setname("M");
	cat1[6].setrange(0, 1000);
	cat1[6].setval(0, 0, 500, 1000);

	cat1[7].setname("P");
	cat1[7].setrange(500, 1400);
	cat1[7].setval(500, 1000, 1200, 1400);

	cat1[8].setname("MP");
	cat1[8].setrange(1400, 2000);
	cat1[8].setval(1400, 1500, 2000, 2000);


	/*Defini-se a Vari�vel lingu�stica Error*/

	sens_front.setname("Sensores da frente");

	sens_front.includecategory(&cat1[6]);

	sens_front.includecategory(&cat1[7]);

	sens_front.includecategory(&cat1[8]);

	/*
	 RT = Rapido pra Tr�s
	 MT = M�dio pra Tr�s
	 DT = Devagar pra Tr�s
	 DF = Devagar pra Frente
	 MF = M�dio pra Frente
	 RF = R�pido pra Frente
	 */

	/*Define-se os conjuntos fuzzy para a vari�vel lingu�stica Control*/

	cat1[9].setname("RT");
	cat1[9].setrange(-10, -7);
	cat1[9].setval(-10, -10, -8, -7);

	cat1[10].setname("MT");
	cat1[10].setrange(-8,-2);
	cat1[10].setval(-8, -7, -3, -2);

	cat1[11].setname("DT");
	cat1[11].setrange(-3, 1);
	cat1[11].setval(-3, -2, -1, 1);

	cat1[12].setname("DF");
	cat1[12].setrange(-1, 3);
	cat1[12].setval(-1, 1, 2, 3);

	cat1[13].setname("MF");
	cat1[13].setrange(2, 8);
	cat1[13].setval(2, 3, 7, 8);

	cat1[14].setname("RF");
	cat1[14].setrange(7, 10);
	cat1[14].setval(7, 8, 10, 10);


	/*Defini-se a vari�vel lingu�stica Control*/

	lingRightMotor.setname("Controle");



	lingRightMotor.includecategory(&cat1[9]);

	lingRightMotor.includecategory(&cat1[10]);

	lingRightMotor.includecategory(&cat1[11]);
	
	lingRightMotor.includecategory(&cat1[12]);
	lingRightMotor.includecategory(&cat1[13]);

	lingRightMotor.includecategory(&cat1[14]);

/*Defini-se o m�todo defuzzifica��o*/

fuzzycontrolD.set_defuzz(CENTEROFAREA);


/* Defini-se o fuzzy_control pelas entradas fuzzy( Error, DeltaError)
e sa�das (Control) )*/

fuzzycontrolD.definevars(sens_left, sens_front, sens_right, lingRightMotor);



/*Deve-se incluir cada regra fuzzy no fuzzy_control*/



	//Regras para Muito Perto com o sensor da esquerda
	//girar K-Junior para a direita


	fuzzycontrolD.insert_rule("M","M","M","RF");
	fuzzycontrolD.insert_rule("M","M","P","MF");
	fuzzycontrolD.insert_rule("M","M","MP","RF");

	fuzzycontrolD.insert_rule("M","P","M","DF");
	fuzzycontrolD.insert_rule("M","P","P","MF");
	fuzzycontrolD.insert_rule("M","P","MP","RF");

	fuzzycontrolD.insert_rule("M","MP","M","RF");
	fuzzycontrolD.insert_rule("M","MP","P","RF");
	fuzzycontrolD.insert_rule("M","MP","MP","RF");

	//Regras para M�dio com sensor esquerda
	//girar K-Junior para a direita

	fuzzycontrolD.insert_rule("P","M","M","MF");
	fuzzycontrolD.insert_rule("P","M","P","RF");
	fuzzycontrolD.insert_rule("P","M","MP","MF");


	fuzzycontrolD.insert_rule("P","P","M","DT");
	fuzzycontrolD.insert_rule("P","P","P","MF");
	fuzzycontrolD.insert_rule("P","P","MP","MF");

	fuzzycontrolD.insert_rule("P","MP","M","MT");
	fuzzycontrolD.insert_rule("P","MP","P","DF");
	fuzzycontrolD.insert_rule("P","MP","MP","DF");
	

	//Regras para Muito Perto com o sensor da direita
	//girar K-Junior para a esquerda
	
	fuzzycontrolD.insert_rule("MP","M","M","DT");
	fuzzycontrolD.insert_rule("MP","M","P","DF");
	fuzzycontrolD.insert_rule("MP","M","MP","DT");
	
	fuzzycontrolD.insert_rule("MP","P","M","MT");
	fuzzycontrolD.insert_rule("MP","P","P","MF");
	fuzzycontrolD.insert_rule("MP","P","MP","DT");
		
	fuzzycontrolD.insert_rule("MP","MP","M","DT");
	fuzzycontrolD.insert_rule("MP","MP","P","DT");
	fuzzycontrolD.insert_rule("MP","MP","MP","DF");


// Define-se a leitura dos sensores do seu sistema
float ErrorInput = -100.0;
float DeltaErrorInput = 0.0;

float min;
char fc1filename[20];



fuzzycontrolD.set_defuzz(CENTEROFAREA);

// Teste para os controles

//min =  navio(fc,1);
//  printf("Minimum Error = %f\n", min);
  fuzzycontrolD.save_m("controlebottom", 0);
}

float rightMotor::makeInference(float input1, float input2, float input3){
	return fuzzycontrolD.make_inference(input1, input2, input3);
}
