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
int main(){
	int opcion;
	
	cout << "Menu" << endl;
	cout << "1. Complemento a 1 " << endl;
	cout << "2. Complemento a 2 " << endl;
	cout << "3. Signo-magnitud " << endl;
	cout << "4. Salir" << endl;
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
		
		case 4:
			cout << "Programa finalizado..." << endl;
			break;
		default:
			cout << "Opcion invalida" << endl;
	}
	
	return 0;
}
