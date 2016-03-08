#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <cstdlib>
#include <cmath>

using std::abs;
using std::cout;
using std::cin;
using std::endl;

void print_in_middle(WINDOW *win, int starty, int startx, int width, char* string);
int**newArray();
void deletePunteros(int** arreglo, int size);
void llenarMatriz(int** array, int size);
void imprimirTablero(int** array, int size);
bool validacionPieza(int** array, int x, int y, int jugador);
bool movimientoValido(int** array, int posX, int posY, int movX, int movY);
bool movimientoPeon(int** array, int posX, int posY, int movX, int movY, int bandera, int jugador);
bool movimientoTorre(int** array, int posX, int posY, int movX, int movY, int jugador);
bool movimientoAlfil(int** array, int posX, int posY, int movX, int movY, int jugador);
bool movimientoCaballo(int** array, int posX, int posY, int movX, int movY, int jugador);
bool movimientoReina(int** array, int posX, int posY, int movX, int movY, int jugador);
bool movimientoRey(int** array, int posX, int posY, int movX, int movY, int jugador);
char* movimientoTodos(int numTurnos);
void deleteMov(char* movimiento);
void moverTexto(char* movimiento, int turno, int numTurnos);
int verificarPosicionX(char* posicionX);
int verificarPosicionY(char* posicionY);

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
		char* agregarPiezas=movimientoTodos(5);
		do{
			if (bandera==1){
				imprimirTablero(tablero, size);
				refresh();
				moverTexto(agregarPiezas, 1, 5);
				agregarPiezas[0]=verificarPosicionX(agregarPiezas);
				agregarPiezas[1]=verificarPosicionY(agregarPiezas);
				agregarPiezas[2]=verificarPosicionX(agregarPiezas);
				agregarPiezas[3]=verificarPosicionY(agregarPiezas);
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
					//cout<<agregarPiezas[0]<<"  "<<agregarPiezas[1]<<"  "<<agregarPiezas[2]<<"  "<<agregarPiezas[3]<<endl;
					//cout<<validarMov<<endl;
					if (validarMov==false){
						print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"Movimiento invalido "));
						getch();
						clear();
						echo();
					}else if(validarMov==true){
						if (tablero[agregarPiezas[0]][agregarPiezas[1]]==1){
							bool torre=movimientoTorre(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							//cout<<torre<<endl;
							if (torre==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=1;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==2){
							bool alfil=movimientoAlfil(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							//cout<<alfil<<endl;
							if (alfil==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=2;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==3){
							bool caballo=movimientoCaballo(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							//cout<<caballo<<endl;
							if (caballo==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=3;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==4){
							bool reina=movimientoReina(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							//cout<<reina<<endl;
							if (reina==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=4;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==5){
							bool rey=movimientoRey(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							//cout<<rey<<endl;
							if (rey==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=5;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==6){
							if (agregarPiezas[0]==6){
								bool peon=movimientoPeon(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1,1);
								//cout<<peon<<endl;
								if (peon==true){
									tablero[agregarPiezas[2]][agregarPiezas[3]]=6;
									tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
									bandera=2;
								}
							}else{
								bool peon=movimientoPeon(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 0,1);
								//cout<<peon<<endl;
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
				imprimirTablero(tablero, size);
				refresh();
				moverTexto(agregarPiezas, 1, 5);
				agregarPiezas[0]=verificarPosicionX(agregarPiezas);
				agregarPiezas[1]=verificarPosicionY(agregarPiezas);
				agregarPiezas[2]=verificarPosicionX(agregarPiezas);
				agregarPiezas[3]=verificarPosicionY(agregarPiezas);
				print_in_middle(stdscr, LINES / 2+6, -4, 0, strcpy(string,"JUGADOR 2: "));
				print_in_middle(stdscr, LINES / 2+7, -4, 0, strcpy(string,"Ingrese Pieza a Mover: "));
				if (validacionPieza(tablero, agregarPiezas[0], agregarPiezas[1], 2)==true){
					print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"No hay pieza suya en esa posicion "));
					getch();
					clear();
					echo();
				}else if(validacionPieza(tablero, agregarPiezas[0], agregarPiezas[1], 2)==false){
					moverTexto(agregarPiezas, 2, 5);
					print_in_middle(stdscr, LINES / 2+8, -4, 0, strcpy(string,"Ingrese Posicion: "));
					noecho();
					bool validarMov= movimientoValido(tablero, agregarPiezas[0],agregarPiezas[1],agregarPiezas[2],agregarPiezas[3]);
					//cout<<agregarPiezas[0]<<"  "<<agregarPiezas[1]<<"  "<<agregarPiezas[2]<<"  "<<agregarPiezas[3]<<endl;
					//cout<<validarMov<<endl;
					if (validarMov==false){
						print_in_middle(stdscr, LINES / 2+10, -4, 0, strcpy(string,"Movimiento invalido "));
						getch();
						clear();
						echo();
					}else if(validarMov==true){
						if (tablero[agregarPiezas[0]][agregarPiezas[1]]==7){
							bool torre=movimientoTorre(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							//cout<<torre<<endl;
							if (torre==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=7;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==8){
							bool alfil=movimientoAlfil(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							//cout<<alfil<<endl;
							if (alfil==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=8;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==9){
							bool caballo=movimientoCaballo(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							//cout<<caballo<<endl;
							if (caballo==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=9;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==10){
							bool reina=movimientoReina(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							//cout<<reina<<endl;
							if (reina==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=10;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==11){
							bool rey=movimientoRey(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1);
							//cout<<rey<<endl;
							if (rey==true){
								tablero[agregarPiezas[2]][agregarPiezas[3]]=11;
								tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
								bandera=2;
							}
						}else if (tablero[agregarPiezas[0]][agregarPiezas[1]]==12){
							if (agregarPiezas[0]==12){
								bool peon=movimientoPeon(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 1,1);
								//cout<<peon<<endl;
								if (peon==true){
									tablero[agregarPiezas[2]][agregarPiezas[3]]=12;
									tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
									bandera=2;
								}
							}else{
								bool peon=movimientoPeon(tablero, agregarPiezas[0], agregarPiezas[1], agregarPiezas[2], agregarPiezas[3], 0,1);
								//cout<<peon<<endl;
								if (peon==true){
									tablero[agregarPiezas[2]][agregarPiezas[3]]=12;
									tablero[agregarPiezas[0]][agregarPiezas[1]]=0;
									bandera=2;
								}
							}
						} 
					}
				}
			}
		}while(win==false);
		deleteMov(agregarPiezas);
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
	array[size-1][1] = array[size-1][size-2] = 3;
	array[size-1][2] = array[size-1][size-3] = 2;
	array[size-1][size-4] = 4;
	array[size-1][size-5] = 5;
	array[0][0] = array[0][size-1] = 7;
	array[0][1] = array[0][size-2] = 9;
	array[0][2] = array[0][size-3] = 8;
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
char* movimientoTodos(int numTurnos){
    char* movimiento = new char[numTurnos]; 
    return movimiento;
}
void moverTexto(char* movimiento, int turno, int numTurnos){
	int contador = 0;
    while(contador < (numTurnos -1)){
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
    movimiento[numTurnos] = '\0';
}
void deleteMov(char* movimiento){    
    delete [] movimiento;
}
int verificarPosicionX(char* posicionX){//evitar segmentation fault
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
int verificarPosicionY(char* posicionY){
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
    }else if (( posicionY[1] == posiblesY[7] )){
        return 7;
    }
} 