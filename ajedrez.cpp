#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>

using std::abs;
using std::ofstream;
using std::ifstream;

void print_in_middle(WINDOW *win, int starty, int startx, int width, char* string);
int**newArray();
void deletePunteros(int** matrizTablero, int size);
void llenarMatriz(int** matrizTablero, int size);
void imprimirTablero(int** matrizTablero, int size);
bool validacionPieza(int** matrizTablero, int x, int y, int jugador);
bool movimientoValido(int** matrizTablero, int posX, int posY, int movX, int movY);
bool movimientoPeon(int** matrizTablero, int posX, int posY, int movX, int movY, int bandera, int jugador);
bool movimientoTorre(int** matrizTablero, int posX, int posY, int movX, int movY, int jugador);
bool movimientoAlfil(int** matrizTablero, int posX, int posY, int movX, int movY, int jugador);
bool movimientoCaballo(int** matrizTablero, int posX, int posY, int movX, int movY, int jugador);
bool movimientoReina(int** matrizTablero, int posX, int posY, int movX, int movY, int jugador);
bool movimientoRey(int** matrizTablero, int posX, int posY, int movX, int movY, int jugador);
/*void guardar(int** matrizTablero, int size);
void cargar(int** matrizTablero, int size);*/
char* guardarMovimiento(int numCaracteres);
void deleteArreglo(char* movimiento);
void adquirirMovimiento(char* movimiento, int turno, int numCaracteres);
int verificarPosicionX1(char* posicionX);
int verificarPosicionX2(char* posicionX);
int verificarPosicionY1(char* posicionY);
int verificarPosicionY2(char* posicionY);
//void preguntaGuardarCargar(int** matrizTablero, int size);

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
		llenarMatriz(tablero, size);
		char* agregarPiezas=guardarMovimiento(5);
		do{
			if (bandera==1){
				//preguntaGuardarCargar(tablero,size);
				imprimirTablero(tablero, size);
				refresh();
				adquirirMovimiento(agregarPiezas, 1, 5);
				agregarPiezas[0]=verificarPosicionX1(agregarPiezas);
				agregarPiezas[1]=verificarPosicionY1(agregarPiezas);
				agregarPiezas[2]=verificarPosicionX2(agregarPiezas);
				agregarPiezas[3]=verificarPosicionY2(agregarPiezas);
				print_in_middle(stdscr, LINES / 2+6, -4, 0, strcpy(string,"JUGADOR 1: "));
				print_in_middle(stdscr, LINES / 2+7, -4, 0, strcpy(string,"Ingrese Pieza a Mover: "));
				if (validacionPieza(tablero, agregarPiezas[0], agregarPiezas[1], 1)==true){
					print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"No hay pieza suya en esa posicion "));
					getch();
					clear();
					echo();
				}else if(validacionPieza(tablero, agregarPiezas[0], agregarPiezas[1], 1)==false){
					print_in_middle(stdscr, LINES / 2+8, -4, 0, strcpy(string,"Ingrese Posicion: "));
					noecho();
					bool validarMov= movimientoValido(tablero, agregarPiezas[0],agregarPiezas[1],agregarPiezas[2],agregarPiezas[3]);
					if (validarMov==false){
						print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"Movimiento invalido "));
						getch();
						clear();
						echo();
					}else if(validarMov==true){
						if (tablero[agregarPiezas[0]][agregarPiezas[1]]==1){
							bool torre=movimientoTorre(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							if (torre==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=1;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==2){
							bool alfil=movimientoAlfil(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							if (alfil==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=2;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==3){
							bool caballo=movimientoCaballo(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							if (caballo==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=3;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==5){
							bool reina=movimientoReina(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							if (reina==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=5;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==4){
							bool rey=movimientoRey(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							if (rey==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=4;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==6){
							if (agregarPiezas[0]==6){
								bool peon=movimientoPeon(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1,1);
								if (peon==true){
									tablero[agregarPiezas[2]][agregarPiezas[3]]=6;
									tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
									bandera=2;
								}
							}else{
								bool peon=movimientoPeon(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 0,1);
								if (peon==true){
									tablero[agregarPiezas[2]][agregarPiezas[3]]=6;
									tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
									bandera=2;
								}
							}
						} 
					}
				}
			}else if (bandera==2){
				//preguntaGuardarCargar(tablero, size);
				agregarPiezas=guardarMovimiento(5);
				imprimirTablero(tablero, size);
				refresh();
				adquirirMovimiento(agregarPiezas, 2, 5);
				agregarPiezas[0]=verificarPosicionX1(agregarPiezas);
				agregarPiezas[1]=verificarPosicionY1(agregarPiezas);
				agregarPiezas[2]=verificarPosicionX2(agregarPiezas);
				agregarPiezas[3]=verificarPosicionY2(agregarPiezas);
				print_in_middle(stdscr, LINES / 2+6, -4, 0, strcpy(string,"JUGADOR 2: "));
				if (validacionPieza(tablero, agregarPiezas[0], agregarPiezas[1], 2)==true){
					print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"No hay pieza suya en esa posicion "));
					getch();
					clear();
					echo();
				}else if(validacionPieza(tablero, agregarPiezas[0], agregarPiezas[1], 2)==false){
					noecho();
					bool validarMov= movimientoValido(tablero, agregarPiezas[0],agregarPiezas[1],agregarPiezas[2],agregarPiezas[3]);
					if (validarMov==false){
						print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"Movimiento invalido "));
						getch();
						clear();
						echo();
					}else if(validarMov==true){
						if (tablero[agregarPiezas[0]][agregarPiezas[1]]==7){
							bool torre=movimientoTorre(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							if (torre==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=7;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=1;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==8){
							bool alfil=movimientoAlfil(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							if (alfil==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=8;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=1;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==9){
							bool caballo=movimientoCaballo(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							if (caballo==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=9;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=1;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==11){
							bool reina=movimientoReina(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							if (reina==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=11;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=1;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==10){
							bool rey=movimientoRey(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							if (rey==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=10;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=1;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==12){
							if (agregarPiezas[0]==12){
								bool peon=movimientoPeon(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1,1);
								if (peon==true){
									tablero[agregarPiezas[2]][agregarPiezas[3]]=12;
									tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
									bandera=1;
								}
							}else{
								bool peon=movimientoPeon(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 0,1);
								if (peon==true){
									tablero[agregarPiezas[2]][agregarPiezas[3]]=12;
									tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
									bandera=1;
								}
							}
						} 
					}
				}
			}
		}while(win==false);
		deleteArreglo(agregarPiezas);
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
	int**matrizTablero= new int*[size];
	for (int i = 0; i < size; ++i){
		matrizTablero[i]=new int[size];
	}//fin new
	return matrizTablero;
}
void deletePunteros(int** matrizTablero, int size){
	for (int i = 0; i < size; ++i){
		delete[] matrizTablero[i];
	}
	delete[] matrizTablero;//fin delete
}
void llenarMatriz(int** matrizTablero, int size){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if (i==size-2){
				matrizTablero[i][j]=6;
			}else if (i==1){
				matrizTablero[i][j]=12;
			}else{
				matrizTablero[i][j]=0;
			}
		}	
	}
	matrizTablero[size-1][0] = matrizTablero[size-1][size-1] = 1;
	matrizTablero[size-1][1] = matrizTablero[size-1][size-2] = 3;
	matrizTablero[size-1][2] = matrizTablero[size-1][size-3] = 2;
	matrizTablero[size-1][size-4] = 4;
	matrizTablero[size-1][size-5] = 5;
	matrizTablero[0][0] = matrizTablero[0][size-1] = 7;
	matrizTablero[0][1] = matrizTablero[0][size-2] = 9;
	matrizTablero[0][2] = matrizTablero[0][size-3] = 8;
	matrizTablero[0][4] = 10;	
	matrizTablero[0][3] = 11;
}
void imprimirTablero(int** matrizTablero, int size){
	initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_CYAN);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    int movHor = 2,movVer = 1;
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if (matrizTablero[i][j] == 1){//Blancas
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4,"[T]");
			}else if (matrizTablero[i][j] == 2){
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[A]");
			}else if (matrizTablero[i][j] == 3){
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[C]");
			}else if (matrizTablero[i][j] == 4){
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[R]");
			}else if (matrizTablero[i][j] == 5){
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[Q]");				
			}else if (matrizTablero[i][j] == 6){
				attron(COLOR_PAIR(2));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[P]");
			}else if (matrizTablero[i][j] == 7){//Negras
			    attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4,"[T]");
			}else if (matrizTablero[i][j] == 8){
				attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[A]");
			}else if (matrizTablero[i][j] == 9){
				attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[C]");
			}else if (matrizTablero[i][j] == 10){
				attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[R]");
			}else if (matrizTablero[i][j] == 11){
				attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[Q]");
			}else if (matrizTablero[i][j] == 12){
				attron(COLOR_PAIR(1));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[P]");
			}else{
				attron(COLOR_PAIR(3));
				mvprintw((i+movVer)*2,(j+movHor)*4, "[-]");
			}
		}
	}
}
bool validacionPieza(int** matrizTablero, int x, int y, int jugador){
	if (jugador==1){
		if (matrizTablero[x][y]!=1&&matrizTablero[x][y]!=2&&matrizTablero[x][y]!=3&&matrizTablero[x][y]!=4&&matrizTablero[x][y]!=5&&matrizTablero[x][y]!=6){
			return true;
		}
	}else if (jugador==2){
		if (matrizTablero[x][y]!=7&&matrizTablero[x][y]!=8&&matrizTablero[x][y]!=9&&matrizTablero[x][y]!=10&&matrizTablero[x][y]!=11&&matrizTablero[x][y]!=12){
			return true;
		}
	}
	return false;
}
bool movimientoValido(int** matrizTablero, int posX, int posY, int movX, int movY){
	int absX = posY - movY;
	int absY = posX - movX;
	if(absX == 0){ //Movimiento Vertical 
		for(int i = 1;i < abs(absY); i++){
			if(matrizTablero[movX][movY]!=0){
				return false;
			}
		}
	}else if(absY == 0){ //Movimiento Horizontal
		for(int i = 1; i < abs(absX); i++){
			if(matrizTablero[movX][movY]!=0){
				return false;
			}
		}        
	}else if(abs(absX) == abs(absY)){ //Movimiento diagonal
		for(int i = 1; i < abs(absY); i++){
			if(matrizTablero[movX][movY]!=0){
				return false;
			}
		}
	}
	return true;
}
bool movimientoPeon(int** matrizTablero, int posX, int posY, int movX, int movY, int bandera, int jugador){
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
	}else if((abs(absY) == 1)&& (matrizTablero[movX][movY]==0)){//Movida para comer
		if (jugador==1){
        	if (matrizTablero[movX-1][movY]==7||matrizTablero[movX-1][movY]==8||matrizTablero[movX-1][movY]==9||matrizTablero[movX-1][movY]==10||matrizTablero[movX-1][movY]==11||matrizTablero[movX-1][movY]==12){
        		return true;
			}
        }else if(jugador==2){
        	if (matrizTablero[movX+1][movY]==1||matrizTablero[movX+1][movY]==2||matrizTablero[movX+1][movY]==3||matrizTablero[movX+1][movY]==4||matrizTablero[movX+1][movY]==5||matrizTablero[movX+1][movY]==6){
        		return true;
			}
        }
	}
    return false;
}
bool movimientoTorre(int** matrizTablero, int posX, int posY, int movX, int movY, int jugador){
    int absY = posY - movY;
    int absX = posX - movX;
    if((absX == 0) || (absY == 0) ){
        if(movimientoValido(matrizTablero, posX,posY, movX, movY)){            
            if (jugador==1){
	        	if (matrizTablero[movX][movY]!=1||matrizTablero[movX][movY]!=2||matrizTablero[movX][movY]!=3||matrizTablero[movX][movY]!=4||matrizTablero[movX][movY]!=5||matrizTablero[movX][movY]!=6){
					return true;
				}
	        }else if(jugador==2){
	        	if (matrizTablero[movX][movY]!=7||matrizTablero[movX][movY]!=8||matrizTablero[movX][movY]!=9||matrizTablero[movX][movY]!=10||matrizTablero[movX][movY]!=11||matrizTablero[movX][movY]!=12){
	        		return true;
				}
	        }
        }
    }
    return false;
}
bool movimientoAlfil(int** matrizTablero, int posX, int posY, int movX, int movY, int jugador){
    int absY = posY - movY;
    int absX = posX - movX;
    if(abs(absX)==abs(absY)){
        if(movimientoValido(matrizTablero, posX,posY, movX, movY)){            
            if (jugador==1){
	        	if (matrizTablero[movX][movY]!=1||matrizTablero[movX][movY]!=2||matrizTablero[movX][movY]!=3||matrizTablero[movX][movY]!=4||matrizTablero[movX][movY]!=5||matrizTablero[movX][movY]!=6){
					return true;
				}
	        }else if(jugador==2){
	        	if (matrizTablero[movX][movY]!=7||matrizTablero[movX][movY]!=8||matrizTablero[movX][movY]!=9||matrizTablero[movX][movY]!=10||matrizTablero[movX][movY]!=11||matrizTablero[movX][movY]!=12){
	        		return true;
				}
	        }
        }
    }
    return false;
}
bool movimientoCaballo(int** matrizTablero, int posX, int posY, int movX, int movY, int jugador){
	int absY = posY - movY;
	int absX = posX - movX;
	if(((abs(absX) == 2) && (abs(absY) == 1))||((abs(absX) == 1) && (abs(absY) == 2))){
		if (jugador==1){
        	if (matrizTablero[movX][movY]!=1||matrizTablero[movX][movY]!=2||matrizTablero[movX][movY]!=3||matrizTablero[movX][movY]!=4||matrizTablero[movX][movY]!=5||matrizTablero[movX][movY]!=6){
				return true;
			}
        }else if(jugador==2){
        	if (matrizTablero[movX][movY]!=7||matrizTablero[movX][movY]!=8||matrizTablero[movX][movY]!=9||matrizTablero[movX][movY]!=10||matrizTablero[movX][movY]!=11||matrizTablero[movX][movY]!=12){
        		return true;
			}
        }
    }
    return false;
}
bool movimientoReina(int** matrizTablero, int posX, int posY, int movX, int movY, int jugador){
	return (movimientoTorre(matrizTablero, posX, posY, movX, movY, jugador)||movimientoAlfil(matrizTablero, posX, posY, movX, movY, jugador));
}
bool movimientoRey(int** matrizTablero, int posX, int posY, int movX, int movY, int jugador){
    int absY = posY - movY;
    int absX = posX - movX;
    if(abs(absX)==1&&(abs(absY)==1)){
        if(movimientoValido(matrizTablero, posX,posY, movX, movY)){            
            if (jugador==1){
	        	if (matrizTablero[movX][movY]!=1||matrizTablero[movX][movY]!=2||matrizTablero[movX][movY]!=3||matrizTablero[movX][movY]!=4||matrizTablero[movX][movY]!=5||matrizTablero[movX][movY]!=6){
					return true;
				}
	        }else if(jugador==2){
	        	if (matrizTablero[movX][movY]!=7||matrizTablero[movX][movY]!=8||matrizTablero[movX][movY]!=9||matrizTablero[movX][movY]!=10||matrizTablero[movX][movY]!=11||matrizTablero[movX][movY]!=12){
	        		return true;
				}
	        }
        }
    }
    return false;
}
/*void guardar(int** matrizTablero, int size){
	ofstream file("partidaAjedrez.txt");
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			file<<matrizTablero[i][j];
		}
	}
	file.flush();
	file.close();
} 
void cargar(int** matrizTablero, int size){
	ifstream file("partidaAjedrez.txt");
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			file>>matrizTablero[i][j];
		}
	}
	file.close();
}*/ 
char* guardarMovimiento(int numCaracteres){
    char* movimiento = new char[numCaracteres]; 
    return movimiento;
}
void adquirirMovimiento(char* movimiento, int turno, int numCaracteres){
	int contador = 0;
    while(contador < (numCaracteres -1)){
        noecho();
        char temp;
        temp = getch();
        if(((temp >= 65 && temp <= 72) || (temp >= 97 && temp <= 104)) && ((contador == 0) || contador ==2) ){
            echo();
            addch(temp);
            movimiento[contador] = temp;
            contador++;
        }
        if((temp >= '1' && temp <= '8') && ((contador == 1) || contador==3)){
            echo();
            addch(temp);
            movimiento[contador] = temp;
            contador++;
        }
    }
    movimiento[numCaracteres] = '\0';
}
void deleteArreglo(char* movimiento){    
    delete [] movimiento;
}
int verificarPosicionX1(char* posicionX){//evitar segmentation fault
    char posiblesX[] = {'a','A','b','B','c','C','d','D','e','E','f','F','g','G','h','H','\0'};
    if ((posicionX[0]== posiblesX[0] || posicionX[0]==posiblesX[1])){
        return 0;
    }else if ((posicionX[0] == posiblesX[2] || posicionX[0] == posiblesX[3])){
        return 1;
    }else if ((posicionX[0] == posiblesX[4] || posicionX[0] == posiblesX[5])){
        return 2;
    }else if ((posicionX[0] == posiblesX[6] || posicionX[0] == posiblesX[7])){
        return 3;
    }else if ((posicionX[0] == posiblesX[8] || posicionX[0] == posiblesX[9])){
        return 4;
    }else if ((posicionX[0] == posiblesX[10] || posicionX[0] == posiblesX[11])){
        return 5;
    }else if ((posicionX[0] == posiblesX[12] || posicionX[0] == posiblesX[13])){
        return 6;
    }else if ((posicionX[0] == posiblesX[14] || posicionX[0] == posiblesX[15])){
        return 7;
    }
}
int verificarPosicionX2(char* posicionX){
    char posiblesX[] = {'a','A','b','B','c','C','d','D','e','E','f','F','g','G','h','H','\0'};
    if ((posicionX[2]== posiblesX[0] || posicionX[2]==posiblesX[1])){
        return 0;
    }else if ((posicionX[2] == posiblesX[2] || posicionX[2] == posiblesX[3])){
        return 1;
    }else if ((posicionX[2] == posiblesX[4] || posicionX[2] == posiblesX[5])){
        return 2;
    }else if ((posicionX[2] == posiblesX[6] || posicionX[2] == posiblesX[7])){
        return 3;
    }else if ((posicionX[2] == posiblesX[8] || posicionX[2] == posiblesX[9])){
        return 4;
    }else if ((posicionX[2] == posiblesX[10] || posicionX[2] == posiblesX[11])){
        return 5;
    }else if ((posicionX[2] == posiblesX[12] || posicionX[2] == posiblesX[13])){
        return 6;
    }else if ((posicionX[2] == posiblesX[14] || posicionX[2] == posiblesX[15])){
        return 7;
    }
}
int verificarPosicionY1(char* posicionY){
    char posiblesY[] = {'1','2','3','4','5','6','7','8','\0'};
    if ((posicionY[1]== posiblesY[0])){
        return 0;
    }else if ((posicionY[1]==posiblesY[1])){
        return 1;
    }else if ((posicionY[1]==posiblesY[2] )){
        return 2;
    }else if ((posicionY[1] == posiblesY[3] )){
        return 3;
    }else if ((posicionY[1]== posiblesY[4] )){
        return 4;
    }else if ((posicionY[1] == posiblesY[5] )){
        return 5;
    }else if ((posicionY[1] == posiblesY[6] )){
        return 6;
    }else if ((posicionY[1] == posiblesY[7] )){
        return 7;
    }
} 
int verificarPosicionY2(char* posicionY){
    char posiblesY[] = {'1','2','3','4','5','6','7','8','\0'};
    if ((posicionY[3]== posiblesY[0])){
        return 0;
    }else if ((posicionY[3]==posiblesY[1])){
        return 1;
    }else if ((posicionY[3]==posiblesY[2] )){
        return 2;
    }else if ((posicionY[3] == posiblesY[3] )){
        return 3;
    }else if ((posicionY[3]== posiblesY[4] )){
        return 4;
    }else if ((posicionY[3] == posiblesY[5] )){
        return 5;
    }else if ((posicionY[3] == posiblesY[6] )){
        return 6;
    }else if ((posicionY[3] == posiblesY[7] )){
        return 7;
    }
}
/*void preguntaGuardarCargar(int** matrizTablero, int size){
	char string[25];
	print_in_middle(stdscr, LINES / 2+10, -6, 0, strcpy(string,"Desea guardar la partida, cargar la partida, o seguir jugando? [W/L] "));
	print_in_middle(stdscr, LINES / 2+12, -6, 0, strcpy(string,"Cualquier otra tecla seguira el juego"));
	char temp;
	temp=getch();
	if (temp==87||temp==119){
		guardar(matrizTablero, size);
	}
	if(temp==76||temp==108){
		cargar(matrizTablero, size);
	}
}*/