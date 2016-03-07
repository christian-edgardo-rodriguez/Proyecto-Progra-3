#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>

using std::abs;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

void print_in_middle(WINDOW *win, int starty, int startx, int width, char* string);
int**newArray();
void deletePunteros(int** arreglo, int size);
void llenarMatriz(int** array, int size);
void imprimirTablero(int** array, int size);
bool validacionPieza(int** array, int x, int y, int jugador);
int cambioANumero(char letra);
bool movimientoValido(int** array, int posX, int posY, int movX, int movY);
bool movimientoPeon(int** array, int posX, int posY, int movX, int movY, int bandera, int jugador);
bool movimientoTorre(int** array, int posX, int posY, int movX, int movY, int jugador);
bool movimientoAlfil(int** array, int posX, int posY, int movX, int movY, int jugador);
bool movimientoCaballo(int** array, int posX, int posY, int movX, int movY, int jugador);
bool movimientoReina(int** array, int posX, int posY, int movX, int movY, int jugador);
bool movimientoRey(int** array, int posX, int posY, int movX, int movY, int jugador);

int main(int argc, char *argv[]){
	initscr();
	char string[25];
	print_in_middle(stdscr, LINES / 2, 0, 0, strcpy(string,"Bienvenido al juego de Ajedrez"));
	print_in_middle(stdscr, LINES / 2+2, 0, 0, strcpy(string,"Proyecto de Progra 3"));
	getch();
	if(true){
		clear();
		if(has_colors() == FALSE){	
			endwin();
			printf("Your terminal does not support color\n");
			exit(1);
		}
		bool win=false;
		int size=8, bandera=1;	
		int** tablero=newArray();
		vector<int>piezas;
		llenarMatriz(tablero, size);
		int posX, posY, movX, movY;
		do{
			if (bandera==1){
				imprimirTablero(tablero, size);
				refresh();
				print_in_middle(stdscr, LINES / 2+6, -4, 0, strcpy(string,"JUGADOR 1: "));
				print_in_middle(stdscr, LINES / 2+7, -4, 0, strcpy(string,"Ingrese Pieza a Mover: "));
				char temp= getch();
				noecho();
				if (temp == '1' || temp == '2' ||temp == '3' ||temp == '4' ||temp == '5' ||temp == '6' ||temp == '7' ||temp == '8' ){
					echo();
					posX=cambioANumero(temp);
					piezas.push_back(posX);
					char temp2=getch();
					noecho();
					if (temp2 == '1' || temp2 == '2' ||temp2 == '3' ||temp2 == '4' ||temp2 == '5' ||temp2 == '6' ||temp2 == '7' ||temp2 == '8' ){
						echo();
						posY=cambioANumero(temp2);
						piezas.push_back(posY);
						//noecho();
						if (validacionPieza(tablero, piezas.at(0), piezas.at(1), 1)==true){
							print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"No hay pieza suya en esa posicion "));
							getch();
							clear();
							piezas.erase(piezas.begin());
							piezas.erase(piezas.begin());
							echo();
						}else if(validacionPieza(tablero, piezas.at(0), piezas.at(1), 1)==false){
							print_in_middle(stdscr, LINES / 2+8, -4, 0, strcpy(string,"Ingrese Posicion: "));
							char temp3= getch();
							noecho();
							if (temp3 == '1' || temp3 == '2' ||temp3 == '3' ||temp3 == '4' ||temp3 == '5' ||temp3 == '6' ||temp3 == '7' ||temp3 == '8' ){
								echo();
								movX=cambioANumero(temp3);
								piezas.push_back(movX);
								char temp4=getch();
								noecho();
								if (temp4 == '1' || temp4 == '2' ||temp4 == '3' ||temp4 == '4' ||temp4 == '5' ||temp4 == '6' ||temp4 == '7' ||temp4 == '8' ){
									echo();
									movY=cambioANumero(temp4);
									piezas.push_back(movY);
									noecho();
									bool validarMov= movimientoValido(tablero, piezas.at(0),piezas.at(1),piezas.at(2),piezas.at(3));
									cout<<piezas.at(0)<<"  "<<piezas.at(1)<<"  "<<piezas.at(2)<<"  "<<piezas.at(3)<<endl;
									cout<<validarMov<<endl;
									if (validarMov==false){
										print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"Movimiento invalido "));
										getch();
										clear();
										piezas.erase(piezas.begin());
										piezas.erase(piezas.begin());
										piezas.erase(piezas.begin());
										piezas.erase(piezas.begin());
										echo();
									}else if(validarMov==true){
										if (tablero[posX][posY]==1){
											bool torre=movimientoTorre(tablero, posX, posY, movX, movY, 1);
											cout<<torre<<endl;
											if (torre==true){
												tablero[movX][movY]=1;
												tablero[posX][posY]=0;
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												bandera=2;
											}
										}else if (tablero[posX][posY]==2){
											bool alfil=movimientoAlfil(tablero, posX, posY, movX, movY, 1);
											cout<<alfil<<endl;
											if (alfil==true){
												tablero[movX][movY]=2;
												tablero[posX][posY]=0;
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												bandera=2;
											}
										}else if (tablero[posX][posY]==3){
											bool caballo=movimientoCaballo(tablero, posX, posY, movX, movY, 1);
											cout<<caballo<<endl;
											if (caballo==true){
												tablero[movX][movY]=3;
												tablero[posX][posY]=0;
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												bandera=2;
											}
										}else if (tablero[posX][posY]==4){
											bool reina=movimientoReina(tablero, posX, posY, movX, movY, 1);
											cout<<reina<<endl;
											if (reina==true){
												tablero[movX][movY]=4;
												tablero[posX][posY]=0;
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												bandera=2;
											}
										}else if (tablero[posX][posY]==5){
											bool rey=movimientoRey(tablero, posX, posY, movX, movY, 1);
											cout<<rey<<endl;
											if (rey==true){
												tablero[movX][movY]=5;
												tablero[posX][posY]=0;
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												bandera=2;
											}
										}else if (tablero[posX][posY]==6){
											if (posX==6){
												bool peon=movimientoPeon(tablero, posX, posY, movX, movY, 1,1);
												cout<<peon<<endl;
												if (peon==true){
													tablero[movX][movY]=6;
													tablero[posX][posY]=0;
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													bandera=2;
												}
											}else{
												bool peon=movimientoPeon(tablero, posX, posY, movX, movY, 0,1);
												cout<<peon<<endl;
												if (peon==true){
													tablero[movX][movY]=6;
													tablero[posX][posY]=0;
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													bandera=2;
												}
											}
										} 
									}
								}
							}
						}
					}
				}
			}else if (bandera==2){
				imprimirTablero(tablero, size);
				refresh();
				print_in_middle(stdscr, LINES / 2+6, -4, 0, strcpy(string,"JUGADOR 2: "));
				print_in_middle(stdscr, LINES / 2+7, -4, 0, strcpy(string,"Ingrese Pieza a Mover: "));
				char temp5= getch();
				noecho();
				if (temp5 == '1' || temp5 == '2' ||temp5 == '3' ||temp5 == '4' ||temp5 == '5' ||temp5 == '6' ||temp5 == '7' ||temp5 == '8' ){
					echo();
					posX=cambioANumero(temp5);
					piezas.push_back(posX);
					char temp6=getch();
					noecho();
					if (temp6 == '1' || temp6 == '2' ||temp6 == '3' ||temp6 == '4' ||temp6 == '5' ||temp6 == '6' ||temp6 == '7' ||temp6 == '8' ){
						echo();
						posY=cambioANumero(temp6);
						piezas.push_back(posY);
						//noecho();
						if (validacionPieza(tablero, piezas.at(0), piezas.at(1), 1)==true){
							print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"No hay pieza suya en esa posicion "));
							getch();
							clear();
							piezas.erase(piezas.begin());
							piezas.erase(piezas.begin());
							echo();
						}else if(validacionPieza(tablero, piezas.at(0), piezas.at(1), 1)==false){
							print_in_middle(stdscr, LINES / 2+8, -4, 0, strcpy(string,"Ingrese Posicion: "));
							char temp7= getch();
							noecho();
							if (temp7 == '1' || temp7 == '2' ||temp7 == '3' ||temp7 == '4' ||temp7 == '5' ||temp7 == '6' ||temp7 == '7' ||temp7 == '8' ){
								echo();
								movX=cambioANumero(temp7);
								piezas.push_back(movX);
								char temp8=getch();
								noecho();
								if (temp8 == '1' || temp8 == '2' ||temp8 == '3' ||temp8 == '4' ||temp8 == '5' ||temp8 == '6' ||temp8 == '7' ||temp8 == '8' ){
									echo();
									movY=cambioANumero(temp8);
									piezas.push_back(movY);
									noecho();
									bool validarMov= movimientoValido(tablero, piezas.at(0),piezas.at(1),piezas.at(2),piezas.at(3));
									cout<<piezas.at(0)<<"  "<<piezas.at(1)<<"  "<<piezas.at(2)<<"  "<<piezas.at(3)<<endl;
									cout<<validarMov<<endl;
									if (validarMov==false){
										print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"Movimiento invalido "));
										getch();
										clear();
										piezas.erase(piezas.begin());
										piezas.erase(piezas.begin());
										piezas.erase(piezas.begin());
										piezas.erase(piezas.begin());
										echo();
									}else if(validarMov==true){
										if (tablero[posX][posY]==1){
											bool torre=movimientoTorre(tablero, posX, posY, movX, movY, 2);
											cout<<torre<<endl;
											if (torre==true){
												tablero[movX][movY]=7;
												tablero[posX][posY]=0;
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												bandera=1;
											}
										}else if (tablero[posX][posY]==2){
											bool alfil=movimientoAlfil(tablero, posX, posY, movX, movY, 2);
											cout<<alfil<<endl;
											if (alfil==true){
												tablero[movX][movY]=8;
												tablero[posX][posY]=0;
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												bandera=1;
											}
										}else if (tablero[posX][posY]==3){
											bool caballo=movimientoCaballo(tablero, posX, posY, movX, movY, 2);
											cout<<caballo<<endl;
											if (caballo==true){
												tablero[movX][movY]=9;
												tablero[posX][posY]=0;
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												bandera=1;
											}
										}else if (tablero[posX][posY]==4){
											bool reina=movimientoReina(tablero, posX, posY, movX, movY, 2);
											cout<<reina<<endl;
											if (reina==true){
												tablero[movX][movY]=10;
												tablero[posX][posY]=0;
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												bandera=1;
											}
										}else if (tablero[posX][posY]==5){
											bool rey=movimientoRey(tablero, posX, posY, movX, movY, 2);
											cout<<rey<<endl;
											if (rey==true){
												tablero[movX][movY]=11;
												tablero[posX][posY]=0;
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												piezas.erase(piezas.begin());
												bandera=2;
											}
										}else if (tablero[posX][posY]==6){
											if (posX==6){
												bool peon=movimientoPeon(tablero, posX, posY, movX, movY, 1,2);
												cout<<peon<<endl;
												if (peon==true){
													tablero[movX][movY]=12;
													tablero[posX][posY]=0;
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													bandera=1;
												}
											}else{
												bool peon=movimientoPeon(tablero, posX, posY, movX, movY, 0,2);
												cout<<peon<<endl;
												if (peon==true){
													tablero[movX][movY]=12;
													tablero[posX][posY]=0;
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													piezas.erase(piezas.begin());
													bandera=1;
												}
											}
										} 
									}
								}
							}
						}
					}
				}
			}
		}while(win==false);
		deletePunteros(tablero, size);
	}		
}
void print_in_middle(WINDOW *win, int starty, int startx, int width, char* string){	
	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	mvprintw(y, x, string);
	refresh();
}
int**newArray(){
	int size=8;
	int**arreglo= new int*[size];
	for (int i = 0; i < size; ++i){
		arreglo[i]=new int[size];
	}//fin new
	return arreglo;
}
void deletePunteros(int** arreglo, int size){
	for (int i = 0; i < size; ++i){
		delete[] arreglo[i];
	}
	delete[] arreglo;//fin delete
}
void llenarMatriz(int** array, int size){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if (i==size-2){
				array[i][j]=6;
			}else if (i==1){
				array[i][j]=12;
			}else{
				array[i][j]=0;
			}
		}	
	}
	array[size-1][0] = array[size-1][size-1] = 1;
	array[size-1][1] = array[size-1][size-2] = 2;
	array[size-1][2] = array[size-1][size-3] = 3;
	array[size-1][size-4] = 4;
	array[size-1][size-5] = 5;
	array[0][0] = array[0][size-1] = 7;
	array[0][1] = array[0][size-2] = 8;
	array[0][2] = array[0][size-3] = 9;
	array[0][4] = 10;	
	array[0][3] = 11;
}
void imprimirTablero(int** array, int size){
	initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_CYAN);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    int movHor = 2,movVer = 1;
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if (array[i][j] == 1){//Blancas
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4,"[T]");
			}else if (array[i][j] == 2){
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[A]");
			}else if (array[i][j] == 3){
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[C]");
			}else if (array[i][j] == 4){
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[R]");
			}else if (array[i][j] == 5){
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[Q]");				
			}else if (array[i][j] == 6){
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[P]");
			}else if (array[i][j] == 7){//Negras
			    attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4,"[T]");
			}else if (array[i][j] == 8){
				attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[A]");
			}else if (array[i][j] == 9){
				attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[C]");
			}else if (array[i][j] == 10){
				attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[R]");
			}else if (array[i][j] == 11){
				attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[Q]");
			}else if (array[i][j] == 12){
				attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[P]");
			}else{
				attron(COLOR_PAIR(3));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[-]");
			}
		}
	}
}
bool validacionPieza(int** array, int x, int y, int jugador){
	if (jugador==1){
		if (array[x][y]!=1&&array[x][y]!=2&&array[x][y]!=3&&array[x][y]!=4&&array[x][y]!=5&&array[x][y]!=6){
			return true;
		}
	}else if (jugador==2){
		if (array[x][y]!=7&&array[x][y]!=8&&array[x][y]!=9&&array[x][y]!=10&&array[x][y]!=11&&array[x][y]!=12){
			return true;
		}
	}
	return false;
}
int cambioANumero(char letra){
	int posX;
	if (letra=='8'){
		posX=7;
	}else if (letra=='7'){
		posX=6;
	}else if (letra=='6'){
		posX=5;
	}else if (letra=='5'){
		posX=4;
	}else if (letra=='4'){
		posX=3;
	}else if (letra=='3'){
		posX=2;
	}else if (letra=='2'){
		posX=1;
	}else if (letra=='1'){
		posX=0;
	}
	return posX;
}
bool movimientoValido(int** array, int posX, int posY, int movX, int movY){
	int absX = posY - movY;
	int absY = posX - movX;
	if(absX == 0){ //Movimiento Vertical 
		for(int i = 1;i < abs(absY); i++){
			if(array[movX][movY]!=0){
				return false;
			}
		}
	}else if(absY == 0){ //Movimiento Horizontal
		for(int i = 1; i < abs(absX); i++){
			if(array[movX][movY]!=0){
				return false;
			}
		}        
	}else if(abs(absX) == abs(absY)){ //Movimiento diagonal
		for(int i = 1; i < abs(absY); i++){
			if(array[movX][movY]!=0){
				return false;
			}
		}
	}
	return true;
}
bool movimientoPeon(int** array, int posX, int posY, int movX, int movY, int bandera, int jugador){
	int absY = posY - movY;
	int absX = posX - movX;
	if(abs(absX) == 1){ //Movida Vertical       
		if(abs(absY) == 0){ //Si mueve un casillero
           	return true;
        }
    }else if(abs(absX) == 2){ //Movida larga de peon
		if(bandera==1){
			return true;
		}
	}else if((abs(absY) == 1)&& (array[movX][movY]==0)){//Movida para comer
		if (jugador==1){
        	if (array[movX-1][movY]==7||array[movX-1][movY]==8||array[movX-1][movY]==9||array[movX-1][movY]==10||array[movX-1][movY]==11||array[movX-1][movY]==12){
        		return true;
			}
        }else if(jugador==2){
        	if (array[movX+1][movY]==1||array[movX+1][movY]==2||array[movX+1][movY]==3||array[movX+1][movY]==4||array[movX+1][movY]==5||array[movX+1][movY]==6){
        		return true;
			}
        }
	}
    return false;
}
bool movimientoTorre(int** array, int posX, int posY, int movX, int movY, int jugador){
    int absY = posY - movY;
    int absX = posX - movX;
    if((absX == 0) || (absY == 0) ){
        if(movimientoValido(array, posX,posY, movX, movY)){            
            if (jugador==1){
	        	if (array[movX][movY]!=1||array[movX][movY]!=2||array[movX][movY]!=3||array[movX][movY]!=4||array[movX][movY]!=5||array[movX][movY]!=6){
					return true;
				}
	        }else if(jugador==2){
	        	if (array[movX][movY]!=7||array[movX][movY]!=8||array[movX][movY]!=9||array[movX][movY]!=10||array[movX][movY]!=11||array[movX][movY]!=12){
	        		return true;
				}
	        }
        }
    }
    return false;
}
bool movimientoAlfil(int** array, int posX, int posY, int movX, int movY, int jugador){
    int absY = posY - movY;
    int absX = posX - movX;
    if(abs(absX)==abs(absY)){
        if(movimientoValido(array, posX,posY, movX, movY)){            
            if (jugador==1){
	        	if (array[movX][movY]!=1||array[movX][movY]!=2||array[movX][movY]!=3||array[movX][movY]!=4||array[movX][movY]!=5||array[movX][movY]!=6){
					return true;
				}
	        }else if(jugador==2){
	        	if (array[movX][movY]!=7||array[movX][movY]!=8||array[movX][movY]!=9||array[movX][movY]!=10||array[movX][movY]!=11||array[movX][movY]!=12){
	        		return true;
				}
	        }
        }
    }
    return false;
}
bool movimientoCaballo(int** array, int posX, int posY, int movX, int movY, int jugador){
	int absY = posY - movY;
	int absX = posX - movX;
	if(((abs(absX) == 2) && (abs(absY) == 1))||((abs(absX) == 1) && (abs(absY) == 2))){
		if (jugador==1){
        	if (array[movX][movY]!=1||array[movX][movY]!=2||array[movX][movY]!=3||array[movX][movY]!=4||array[movX][movY]!=5||array[movX][movY]!=6){
				return true;
			}
        }else if(jugador==2){
        	if (array[movX][movY]!=7||array[movX][movY]!=8||array[movX][movY]!=9||array[movX][movY]!=10||array[movX][movY]!=11||array[movX][movY]!=12){
        		return true;
			}
        }
    }
    return false;
}
bool movimientoReina(int** array, int posX, int posY, int movX, int movY, int jugador){
	return (movimientoTorre(array, posX, posY, movX, movY, jugador)||movimientoAlfil(array, posX, posY, movX, movY, jugador));
}
bool movimientoRey(int** array, int posX, int posY, int movX, int movY, int jugador){
    int absY = posY - movY;
    int absX = posX - movX;
    if(abs(absX)==1&&(abs(absY)==1)){
        if(movimientoValido(array, posX,posY, movX, movY)){            
            if (jugador==1){
	        	if (array[movX][movY]!=1||array[movX][movY]!=2||array[movX][movY]!=3||array[movX][movY]!=4||array[movX][movY]!=5||array[movX][movY]!=6){
					return true;
				}
	        }else if(jugador==2){
	        	if (array[movX][movY]!=7||array[movX][movY]!=8||array[movX][movY]!=9||array[movX][movY]!=10||array[movX][movY]!=11||array[movX][movY]!=12){
	        		return true;
				}
	        }
        }
    }
    return false;
}