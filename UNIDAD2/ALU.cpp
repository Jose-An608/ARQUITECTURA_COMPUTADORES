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

int main(){
	int opcion;
	
	cout << "Menu" << endl;
	cout << "1. Complemento a 1 " << endl;
	cout << "2. Complemento a 2 " << endl;
	cout << "3. Signo-magnitud " << endl;
	cout << "4. Suma binaria sin signo " << endl;
	cout << "5. Suma binaria con signo " << endl;
	cout << "6. Multiplicacion sin signo " << endl;
	cout << "7. Salir" << endl;
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
			
			string sig = signoMagnitud(num, bits);
			
			if(sig == "ERROR"){
        		cout << "El numero no cabe en "
            	 << bits << " bits." << endl;
    		}else{
        		cout << "Signo-Magnitud: " << sig << endl;
    		}
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
		
		    string bin1 = decimalAComplemento2(num1, bits);
		    string bin2 = decimalAComplemento2(num2, bits);
		
		    string resultado = sumaConSigno(num1, num2, bits);
		
		    cout << "Numero 1: " << bin1 << endl;
		    cout << "Numero 2: " << bin2 << endl;
		    cout << "Suma: " << resultado << endl;
		
		    break;
		}
		
		case 6:{
		    int num1,num2,bits;
		
		    cout << "Multiplicando: ";
		    cin >> num1;
		
		    cout << "Multiplicador: ";
		    cin >> num2;
		
		    cout << "Bits: ";
		    cin >> bits;
		
		    string M = ajustarBits(decimalAAbinario(num1), bits);
		    string Q = ajustarBits(decimalAAbinario(num2), bits);
		
		    string resultado = multiplicacionSinSigno(M,Q,bits);
		
		    cout << "\nM = " << M << endl;
		    cout << "Q = " << Q << endl;
		    cout << "Resultado = " << resultado << endl;
		
		    break;
		}
		
		case 7:
			cout << "Programa finalizado..." << endl;
			break;
		default:
			cout << "Opcion invalida" << endl;
	}
	
	return 0;
}
