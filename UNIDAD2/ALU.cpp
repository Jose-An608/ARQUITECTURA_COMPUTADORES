#include <iostream>
#include <string>
using namespace std;

string decimalAAbinario(int n){
	if (n == 0){
		return "0";
	}
	
	string binario="";
	
	while(n>0){
        binario = char((n % 2) + '0') + binario;
        n = n/2;
    }
	
	return binario;
}

string ajustarBits(string bin, int bits){
	while(bin.length()<bits){
		bin = "0" + bin;
	}
	return bin;
}
string complementoA1(string bin){
	for(int i=0; i<bin.length(); i++){
		if(bin[i] == '0'){
			bin[i] = '1';
 		}else{
 			bin[i] = '0';
		 }
	}
	return bin;
}

string complementoA2(string bin){
	bin = complementoA1(bin);
	for(int i = bin.length()-1; i>=0; i--){
		if(bin[i]== '0'){
			bin[i] = '1';
			return bin;
		}else{
			bin[i] ='0';
		}
	}
	
	return "1" + bin;
}

string decimalAComplemento2(int num, int bits){
    if(num >= 0){
        return ajustarBits(decimalAAbinario(num), bits);
    }

    string bin = ajustarBits(decimalAAbinario(-num), bits);

    bin = complementoA2(bin);

    if(bin.length() > bits){
        bin = bin.substr(bin.length()-bits);
    }

    return bin;
}

int complemento2ADecimal(string bin){
    if(bin[0] == '0'){
        int valor = 0;

        for(int i=0; i<bin.length(); i++){
            valor = valor * 2 + (bin[i]-'0');
        }

        return valor;
    }

    string temp = complementoA2(bin);

    int valor = 0;

    for(int i=0; i<temp.length(); i++){
        valor = valor * 2 + (temp[i]-'0');
    }

    return -valor;
}

string signoMagnitud(int num, int bits){
	bool negativo = false;
	
	if(num<0){
		negativo = true;
		num = -num;
	}
	
	string bin = decimalAAbinario(num);
	
	if(bin.length() > bits - 1){
		return "Error";
	}
	
	while(bin.length()<bits-1){
		bin = "0" + bin;
	}
	
	if(negativo){
		bin = "1" + bin;
	}else{
		bin = "0" + bin;
	}
	
	return bin;
}

string sumaSinSigno(string bin1, string bin2){
	string resultado = "";
	int acarreo = 0;
	for(int i = bin1.length()-1; i>=0; i--){
		int suma = (bin1[i]-'0')+(bin2[i]-'0') + acarreo;
		resultado = char((suma%2) + '0') + resultado;
		acarreo = suma/2;
		
		}
		if(acarreo == 1){
			resultado = "1" + resultado;
		}
		return resultado;
}


string sumaConSigno(int num1, int num2, int bits){

    string bin1 = decimalAComplemento2(num1, bits);
    string bin2 = decimalAComplemento2(num2, bits);

    string suma = sumaSinSigno(bin1, bin2);

    if(suma.length() > bits){
        suma = suma.substr(suma.length() - bits);
    }

    return suma;
}

string desplazarDerecha(string AQ){
    AQ = "0" + AQ;
    AQ.erase(AQ.length()-1,1);
    return AQ;
}

string multiplicacionSinSigno(string M, string Q, int bits){

    string A(bits,'0');

    for(int i=0; i<bits; i++){

        if(Q[bits-1]=='1'){
            A = sumaSinSigno(A,M);

            if(A.length()>bits){
                A = A.substr(A.length()-bits);
            }
        }

        string AQ = A + Q;

        AQ = desplazarDerecha(AQ);

        A = AQ.substr(0,bits);
        Q = AQ.substr(bits,bits);
    }

    return A + Q;
}

string desplazamientoAritmetico(string A, string Q, char &Q1){

    char signo = A[0];

    Q1 = Q[Q.length()-1];

    Q = A[A.length()-1] + Q.substr(0,Q.length()-1);

    A = signo + A.substr(0,A.length()-1);

    return A + Q;
}

string multiplicacionBooth(int multiplicando, int multiplicador, int bits){

    string M = decimalAComplemento2(multiplicando,bits);

    string negM = complementoA2(M);

    if(negM.length() > bits){
        negM = negM.substr(negM.length()-bits);
    }

    string Q = decimalAComplemento2(multiplicador,bits);

    string A(bits,'0');

    char Q1 = '0';

    for(int i=0;i<bits;i++){

        string ultimos = "";
        ultimos += Q[bits-1];
        ultimos += Q1;

        if(ultimos == "10"){
            A = sumaSinSigno(A,negM);

            if(A.length()>bits){
                A = A.substr(A.length()-bits);
            }
        }
        else if(ultimos == "01"){
            A = sumaSinSigno(A,M);

            if(A.length()>bits){
                A = A.substr(A.length()-bits);
            }
        }

        string AQ = desplazamientoAritmetico(A,Q,Q1);

        A = AQ.substr(0,bits);
        Q = AQ.substr(bits,bits);
    }

    return A + Q;
}

bool estaEnRangoComplemento2(int num, int bits){
    int minimo = -(1 << (bits - 1));
    int maximo = (1 << (bits - 1)) - 1;

    return num >= minimo && num <= maximo;
}

void mostrarRangoComplemento2(int bits){
    int minimo = -(1 << (bits - 1));
    int maximo = (1 << (bits - 1)) - 1;

    cout << "Rango permitido: ["
         << minimo << ", "
         << maximo << "]" << endl;
}

void mostrarRangoSignoMagnitud(int bits){
    int maximo = (1 << (bits - 1)) - 1;

    cout << "Rango permitido: ["
         << -maximo << ", "
         << maximo << "]" << endl;
}

string restaBinaria(string A, string M){
    string comp2 = complementoA2(M);

    if(comp2.length() > M.length()){
        comp2 = comp2.substr(comp2.length()-M.length());
    }

    string resultado = sumaSinSigno(A, comp2);

    if(resultado.length() > A.length()){
        resultado = resultado.substr(resultado.length()-A.length());
    }

    return resultado;
}

string desplazarIzquierda(string A, string Q){
    string AQ = A + Q;

    AQ.erase(0,1);
    AQ += "0";

    return AQ;
}

void divisionSinSigno(int dividendo, int divisor, int bits){

    if(divisor == 0){
        cout << "Error: division entre cero." << endl;
        return;
    }

    string M = ajustarBits(decimalAAbinario(divisor), bits);
    string Q = ajustarBits(decimalAAbinario(dividendo), bits);
    string A(bits,'0');

    for(int i=0; i<bits; i++){

        string AQ = desplazarIzquierda(A,Q);

        A = AQ.substr(0,bits);
        Q = AQ.substr(bits,bits);

        A = restaBinaria(A,M);

        if(A[0] == '1'){ 

            Q[bits-1] = '0';

            A = sumaSinSigno(A,M);

            if(A.length() > bits){
                A = A.substr(A.length()-bits);
            }
        }
        else{
            Q[bits-1] = '1';
        }
    }

    cout << "\nCociente (Q): " << Q << endl;
    cout << "Residuo  (A): " << A << endl;

    int cociente = 0;
    int residuo = 0;

    for(int i=0; i<Q.length(); i++){
        cociente = cociente*2 + (Q[i]-'0');
    }

    for(int i=0; i<A.length(); i++){
        residuo = residuo*2 + (A[i]-'0');
    }

    cout << "Cociente decimal: " << cociente << endl;
    cout << "Residuo decimal : " << residuo << endl;
}

int main(){
	int opcion;
	
	cout << "Menu" << endl;
	cout << "1. Complemento a 1 " << endl;
	cout << "2. Complemento a 2 " << endl;
	cout << "3. Signo-magnitud " << endl;
	cout << "4. Suma binaria sin signo " << endl;
	cout << "5. Suma binaria con signo " << endl;
	cout << "6. Multiplicacion sin signo " << endl;
	cout << "7. Multiplicacion con signo " << endl;
	cout << "8. Division sin signo " << endl;
	cout << "9. Salir" << endl;
	cout << "Opcion: " << endl;
	cin >> opcion;
	
	switch(opcion){
		case 1: {
			int opcion2;
			cout << "Escoge: " << endl;
			cout << "1. Decimal " << endl;
			cout << "2. Binario " << endl;
			cout << "3. Salir" << endl;
			cout << "Opcion: " << endl;
			cin >> opcion2;
			
			switch(opcion2){
				case 1: {
					int n, bits;
					cout << "Escriba el decimal: " << endl;
					cin >> n;
					
					bool negativo = false;
					
					if(n<0){
						negativo = true;
						n = -n;
					}
					
					cout << "¿Con cuantos bits quiere trabajar? " << endl;
					cin >> bits;
					                    
					string num2= decimalAAbinario(n);
					
					if(num2.length() > bits){ 
						cout << "Error: el numero no cabe en " 
						<< bits << " bits." << endl; 
						break; 
					}
					
					num2 = ajustarBits(num2, bits);
					
					string comp1 = complementoA1(num2);
					
					cout << "Binario: " << num2 << endl;
					cout << "Complemento a 1: " << comp1;
					break;
				}
				case 2:
					string bin;
					cout << "Escribe el binario: " << endl;
					cin >> bin;
					string comp1 = complementoA1(bin);
					cout << "Complemento a 1: " << comp1;
					break;
			}
			break;
		}
		
		case 2:
			int opcion2;
			cout << "Escoge: " << endl;
			cout << "1. Decimal " << endl;
			cout << "2. Binario " << endl;
			cout << "3. Salir" << endl;
			cout << "Opcion: " << endl;
			cin >> opcion2;
			
			switch(opcion2){
				case 1: {
					int n, bits;
					cout << "Escriba el decimal: " << endl;
					cin >> n;
					
					bool negativo = false;
					
					if(n<0){
						negativo=true;
						n=-n;
					}
					
					cout << "¿Con cuantos bits desea trabajar?: ";
                    cin >> bits;
                    
					string num2= decimalAAbinario(n);
					
					if(num2.length() > bits){
                        cout << "Error: el numero no cabe en "
                             << bits << " bits." << endl;
                        break;
                    }
                    
                    num2 = ajustarBits(num2, bits);
                    
					string comp2 = complementoA2(num2);
					
					cout << "Binario: " << num2 << endl;
					cout << "Complemento a 2: " << comp2;
					break;
				}
				case 2:
					string bin;
					cout << "Escribe el binario: " << endl;
					cin >> bin;
					string comp2 = complementoA2(bin);
					cout << "Complemento a 2: " << comp2;
					break;
			}
			break;
		
		case 3:{
		    int num, bits;
		
		    cout << "Introduce el numero decimal: " << endl;
		    cin >> num;
		
		    cout << "¿Con cuantos bits desea trabajar? " << endl;
		    cin >> bits;
		
		    mostrarRangoSignoMagnitud(bits);
		
		    int maximo = (1 << (bits - 1)) - 1;
		
		    if(num < -maximo || num > maximo){
		        cout << "Error: el numero no cabe en "
		             << bits << " bits." << endl;
		        break;
		    }
		
		    string sig = signoMagnitud(num, bits);
		
		    cout << "Signo-Magnitud: "
		         << sig << endl;
		
		    break;
		}
		
		case 4:{
			int bits, num1, num2;
			cout << "Introduce el primer numero decimal: ";
			cin >> num1;
			cout << "Introduce el segundo numero decimal: ";
			cin >> num2;
			
			cout << "¿Con cuantos bits quisiera trabajar? ";
			cin >> bits;
			
			string bin1 = decimalAAbinario(num1);
			string bin2 = decimalAAbinario(num2);
			
			if(bin2.length()>bits || bin2.length()>bits){
				cout << "Error: alguno de los numeros no cabe en "
             	<< bits << " bits." << endl;
        		break;
			}
			
			bin1 = ajustarBits(bin1,bits);
			bin2 = ajustarBits(bin2, bits);
			
			
			string suma=sumaSinSigno(bin1,bin2);
			
			 cout << "Binario 1: " << bin1 << endl;
    		cout << "Binario 2: " << bin2 << endl;
    		cout << "Suma: " << suma << endl;
			break;
		}
		
		case 5:{
		    int num1, num2, bits;
		
		    cout << "Introduce el primer numero decimal: ";
		    cin >> num1;
		
		    cout << "Introduce el segundo numero decimal: ";
		    cin >> num2;
		
		    cout << "¿Con cuantos bits desea trabajar? ";
		    cin >> bits;
		
		    mostrarRangoComplemento2(bits);
		
		    if(!estaEnRangoComplemento2(num1,bits) ||
		       !estaEnRangoComplemento2(num2,bits)){
		        cout << "Error: alguno de los numeros "
		             << "no cabe en "
		             << bits << " bits." << endl;
		        break;
		    }
		
		    string bin1 = decimalAComplemento2(num1, bits);
		    string bin2 = decimalAComplemento2(num2, bits);
		
		    string resultado = sumaConSigno(num1, num2, bits);
		
		    cout << "Numero 1: "
		         << bin1 << endl;
		
		    cout << "Numero 2: "
		         << bin2 << endl;
		
		    cout << "Suma: "
		         << resultado << endl;
		
		    int sumaDecimal = num1 + num2;
		
		    if(!estaEnRangoComplemento2(sumaDecimal,bits)){
		        cout << "Advertencia: Overflow."
		             << endl;
		    }
		
		    break;
		}
		
		case 6:{
		    int num1, num2, bits;
		
		    cout << "Multiplicando: ";
		    cin >> num1;
		
		    cout << "Multiplicador: ";
		    cin >> num2;
		
		    cout << "Bits: ";
		    cin >> bits;
		
		    int maximo = (1 << bits) - 1;
		
		    cout << "Rango permitido: [0, "
		         << maximo << "]" << endl;
		
		    if(num1 < 0 || num2 < 0 ||
		       num1 > maximo || num2 > maximo){
		        cout << "Error: los numeros "
		             << "no caben en "
		             << bits << " bits." << endl;
		        break;
		    }
		
		    string M = ajustarBits(decimalAAbinario(num1), bits);
		    string Q = ajustarBits(decimalAAbinario(num2), bits);
		
		    string resultado =
		        multiplicacionSinSigno(M,Q,bits);
		
		    cout << "\nM = "
		         << M << endl;
		
		    cout << "Q = "
		         << Q << endl;
		
		    cout << "Resultado = "
		         << resultado << endl;
		
		    break;
		}
		
		case 7:{
		    int num1, num2, bits;
		
		    cout << "Multiplicando: ";
		    cin >> num1;
		
		    cout << "Multiplicador: ";
		    cin >> num2;
		
		    cout << "Bits: ";
		    cin >> bits;
		
		    mostrarRangoComplemento2(bits);
		
		    if(!estaEnRangoComplemento2(num1,bits) ||
		       !estaEnRangoComplemento2(num2,bits)){
		        cout << "Error: alguno de los numeros "
		             << "no cabe en "
		             << bits << " bits." << endl;
		        break;
		    }
		
		    string resultado =
		        multiplicacionBooth(num1,num2,bits);
		
		    cout << "Resultado binario = "
		         << resultado << endl;
		
		    cout << "Resultado decimal = "
		         << complemento2ADecimal(resultado)
		         << endl;
		
		    long long producto =
		        (long long)num1 * num2;
		
		    long long minimo =
		        -(1LL << (2*bits - 1));
		
		    long long maximo =
		        (1LL << (2*bits - 1)) - 1;
		
		    if(producto < minimo ||
		       producto > maximo){
		        cout << "Advertencia: Overflow."
		             << endl;
		    }
		
		    break;
		}
		
		case 8:{
		    int dividendo, divisor, bits;
		
		    cout << "Dividendo: ";
		    cin >> dividendo;
		
		    cout << "Divisor: ";
		    cin >> divisor;
		
		    cout << "Bits: ";
		    cin >> bits;
		
		    int maximo = (1 << bits) - 1;
		
		    cout << "Rango permitido: [0, "
		         << maximo << "]" << endl;
		
		    if(dividendo < 0 || divisor < 0){
		        cout << "Error: la division sin signo "
		             << "solo acepta numeros positivos."
		             << endl;
		        break;
		    }
		
		    if(dividendo > maximo || divisor > maximo){
		        cout << "Error: los numeros no caben en "
		             << bits << " bits." << endl;
		        break;
		    }
		
		    divisionSinSigno(dividendo, divisor, bits);
		
		    break;
		}
		case 9:
			cout << "Programa finalizado..." << endl;
			break;
		default:
			cout << "Opcion invalida" << endl;
	}
	
	return 0;
}
