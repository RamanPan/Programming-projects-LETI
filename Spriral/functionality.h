//
// Created by vpana on 30.09.2022.
//

#ifndef SPRIRAL_FUNCTIONALITY_H
#define SPRIRAL_FUNCTIONALITY_H

void showHelloMessage();

long validation();

void generateSpiral(short I,short J, int area[][J], short variation);

void outputSpiral(int I,int J, int area[][J]);

bool checkOverflow(double d);

void showMenu(int position);

#endif //SPRIRAL_FUNCTIONALITY_H
