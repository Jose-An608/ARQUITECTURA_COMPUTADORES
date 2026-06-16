#include <iostream>
#include <string>
using namespace std;

// ============================================================
// FUNCIONES BASE
// ============================================================

string decimalAAbinario(int n){
    if(n == 0) return "0";
    string binario = "";
    while(n > 0){
        binario = char((n % 2) + '0') + binario;
        n = n / 2;
    }
    return binario;
}

string ajustarBits(string bin, int bits){
    while(bin.length() < bits){
        bin = "0" + bin;
    }
    return bin;
}

// ============================================================
// COMPLEMENTO A 1
// ============================================================

string complementoA1(string bin){
    for(int i = 0; i < bin.length(); i++){
        bin[i] = (bin[i] == '0') ? '1' : '0';
    }
    return bin;
}

// ============================================================
// COMPLEMENTO A 2
// ============================================================

string complementoA2(string bin){
    bin = complementoA1(bin);
    for(int i = bin.length() - 1; i >= 0; i--){
        if(bin[i] == '0'){
            bin[i] = '1';
            return bin;
        } else {
            bin[i] = '0';
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
        bin = bin.substr(bin.length() - bits);
    }
    return bin;
}

int complemento2ADecimal(string bin){
    if(bin[0] == '0'){
        int valor = 0;
        for(int i = 0; i < bin.length(); i++){
            valor = valor * 2 + (bin[i] - '0');
        }
        return valor;
    }
    string temp = complementoA2(bin);
    int valor = 0;
    for(int i = 0; i < temp.length(); i++){
        valor = valor * 2 + (temp[i] - '0');
    }
    return -valor;
}

// ============================================================
// SIGNO-MAGNITUD
// ============================================================

string signoMagnitud(int num, int bits){
    bool negativo = false;
    if(num < 0){
        negativo = true;
        num = -num;
    }
    string bin = decimalAAbinario(num);
    if(bin.length() > bits - 1) return "Error";
    while(bin.length() < bits - 1){
        bin = "0" + bin;
    }
    bin = (negativo ? "1" : "0") + bin;
    return bin;
}

// ============================================================
// SUMA BINARIA SIN SIGNO
// ============================================================

string sumaSinSigno(string bin1, string bin2){
    string resultado = "";
    int acarreo = 0;
    for(int i = bin1.length() - 1; i >= 0; i--){
        int suma = (bin1[i] - '0') + (bin2[i] - '0') + acarreo;
        resultado = char((suma % 2) + '0') + resultado;
        acarreo = suma / 2;
    }
    if(acarreo == 1) resultado = "1" + resultado;
    return resultado;
}

// ============================================================
// SUMA BINARIA CON SIGNO
// ============================================================

string sumaConSigno(int num1, int num2, int bits){
    string bin1 = decimalAComplemento2(num1, bits);
    string bin2 = decimalAComplemento2(num2, bits);
    string suma = sumaSinSigno(bin1, bin2);
    if(suma.length() > bits){
        suma = suma.substr(suma.length() - bits);
    }
    return suma;
}

bool estaEnRangoComplemento2(int num, int bits){
    int minimo = -(1 << (bits - 1));
    int maximo =  (1 << (bits - 1)) - 1;
    return num >= minimo && num <= maximo;
}

// ============================================================
// MULTIPLICACION SIN SIGNO
// ============================================================

string desplazarDerecha(string AQ){
    AQ = "0" + AQ;
    AQ.erase(AQ.length() - 1, 1);
    return AQ;
}

string multiplicacionSinSigno(string M, string Q, int bits){
    string A(bits, '0');
    for(int i = 0; i < bits; i++){
        if(Q[bits - 1] == '1'){
            A = sumaSinSigno(A, M);
            if(A.length() > bits){
                A = A.substr(A.length() - bits);
            }
        }
        string AQ = A + Q;
        AQ = desplazarDerecha(AQ);
        A = AQ.substr(0, bits);
        Q = AQ.substr(bits, bits);
    }
    return A + Q;
}

// ============================================================
// MULTIPLICACION DE BOOTH
// ============================================================

string desplazamientoAritmetico(string A, string Q, char &Q1){
    char signo = A[0];
    Q1 = Q[Q.length() - 1];
    Q = A[A.length() - 1] + Q.substr(0, Q.length() - 1);
    A = signo + A.substr(0, A.length() - 1);
    return A + Q;
}

string multiplicacionBooth(int multiplicando, int multiplicador, int bits){
    string M = decimalAComplemento2(multiplicando, bits);
    string negM = complementoA2(M);
    if(negM.length() > bits){
        negM = negM.substr(negM.length() - bits);
    }
    string Q = decimalAComplemento2(multiplicador, bits);
    string A(bits, '0');
    char Q1 = '0';
    for(int i = 0; i < bits; i++){
        string ultimos = "";
        ultimos += Q[bits - 1];
        ultimos += Q1;
        if(ultimos == "10"){
            A = sumaSinSigno(A, negM);
            if(A.length() > bits) A = A.substr(A.length() - bits);
        } else if(ultimos == "01"){
            A = sumaSinSigno(A, M);
            if(A.length() > bits) A = A.substr(A.length() - bits);
        }
        string AQ = desplazamientoAritmetico(A, Q, Q1);
        A = AQ.substr(0, bits);
        Q = AQ.substr(bits, bits);
    }
    return A + Q;
}

// ============================================================
// RANGOS
// ============================================================

void mostrarRangoComplemento2(int bits){
    int minimo = -(1 << (bits - 1));
    int maximo =  (1 << (bits - 1)) - 1;
    cout << "Rango permitido: [" << minimo << ", " << maximo << "]" << endl;
}

void mostrarRangoSignoMagnitud(int bits){
    int maximo = (1 << (bits - 1)) - 1;
    cout << "Rango permitido: [" << -maximo << ", " << maximo << "]" << endl;
}

// ============================================================
// DIVISION SIN SIGNO
// ============================================================

string restaBinaria(string A, string M){
    string comp2 = complementoA2(M);
    if(comp2.length() > M.length()){
        comp2 = comp2.substr(comp2.length() - M.length());
    }
    string resultado = sumaSinSigno(A, comp2);
    if(resultado.length() > A.length()){
        resultado = resultado.substr(resultado.length() - A.length());
    }
    return resultado;
}

string desplazarIzquierda(string A, string Q){
    string AQ = A + Q;
    AQ.erase(0, 1);
    AQ += "0";
    return AQ;
}

void divisionSinSigno(int dividendo, int divisor, int bits){
    if(divisor == 0){
        cout << "Error: division entre cero." << endl;
        return;
    }
    string M = ajustarBits(decimalAAbinario(divisor),  bits);
    string Q = ajustarBits(decimalAAbinario(dividendo), bits);
    string A(bits, '0');
    for(int i = 0; i < bits; i++){
        string AQ = desplazarIzquierda(A, Q);
        A = AQ.substr(0, bits);
        Q = AQ.substr(bits, bits);
        A = restaBinaria(A, M);
        if(A[0] == '1'){
            Q[bits - 1] = '0';
            A = sumaSinSigno(A, M);
            if(A.length() > bits) A = A.substr(A.length() - bits);
        } else {
            Q[bits - 1] = '1';
        }
    }
    int cociente = 0, residuo = 0;
    for(int i = 0; i < Q.length(); i++) cociente = cociente * 2 + (Q[i] - '0');
    for(int i = 0; i < A.length(); i++) residuo  = residuo  * 2 + (A[i] - '0');
    cout << "\nCociente (Q)    : " << Q << endl;
    cout << "Residuo  (A)    : " << A << endl;
    cout << "Cociente decimal: " << cociente << endl;
    cout << "Residuo decimal : " << residuo  << endl;
}

// ============================================================
// COMA FLOTANTE - IEEE 754 SIMPLE (32 bits)
// ============================================================

string parteFraccionariaBinario(double frac, int precision){
    string bin = "";
    for(int i = 0; i < precision; i++){
        frac *= 2;
        if(frac >= 1.0){
            bin += "1";
            frac -= 1.0;
        } else {
            bin += "0";
        }
    }
    return bin;
}

void representacionComaFlotante(double numero){
    if(numero == 0.0){
        cout << "\nEl numero es cero." << endl;
        cout << "IEEE 754 simple (32 bits): 0 00000000 00000000000000000000000" << endl;
        return;
    }
    int signo = 0;
    if(numero < 0){
        signo = 1;
        numero = -numero;
    }
    int exponente = 0;
    if(numero >= 1.0){
        while(numero >= 2.0){ numero /= 2.0; exponente++; }
    } else {
        while(numero < 1.0){ numero *= 2.0; exponente--; }
    }
    double parteF  = numero - 1.0;
    string fracBits = parteFraccionariaBinario(parteF, 23);
    int sesgo      = 127;
    int expSesgado = exponente + sesgo;
    if(expSesgado <= 0){
        cout << "Advertencia: exponente muy pequeno (desnormalizado o cero)." << endl;
        expSesgado = 0;
    } else if(expSesgado >= 255){
        cout << "Advertencia: exponente muy grande (desbordamiento -> Inf)." << endl;
        expSesgado = 255;
    }
    string sBit    = (signo == 1) ? "1" : "0";
    string expBits = ajustarBits(decimalAAbinario(expSesgado), 8);

    cout << "\n=== Representacion en Coma Flotante ===" << endl;
    cout << "Signo            : " << signo << endl;
    cout << "Mantisa norm.    : 1." << fracBits << endl;
    cout << "Exponente real   : " << exponente << endl;
    cout << "Exponente sesgado: " << exponente << " + " << sesgo
         << " = " << expSesgado << "  ->  " << expBits << endl;
    cout << "\n--- IEEE 754 Precision Simple (32 bits) ---" << endl;
    cout << "S | Exponente |         Mantisa (fraccion)     " << endl;
    cout << sBit << "   " << expBits << "   " << fracBits << endl;
    cout << "Cadena: " << sBit << expBits << fracBits << endl;
}

// ============================================================
// DISEÑO DEL MENU
// ============================================================

void separador(){
    cout << "  +------------------------------------------+" << endl;
}

void mostrarMenu(){
    cout << endl;
    separador();
    cout << "  |     CALCULADORA BINARIA                  |" << endl;
    separador();
    cout << "  |  1. Complemento a 1                      |" << endl;
    cout << "  |  2. Complemento a 2                      |" << endl;
    cout << "  |  3. Signo-Magnitud                       |" << endl;
    cout << "  |  4. Suma sin signo                       |" << endl;
    cout << "  |  5. Suma con signo                       |" << endl;
    cout << "  |  6. Multiplicacion sin signo             |" << endl;
    cout << "  |  7. Multiplicacion con signo (Booth)     |" << endl;
    cout << "  |  8. Division sin signo                   |" << endl;
    cout << "  |  9. Representacion en coma flotante      |" << endl;
    separador();
    cout << "  | 10. Salir                                |" << endl;
    separador();
    cout << "  Opcion: ";
}

// ============================================================
// MAIN
// ============================================================

int main(){
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch(opcion){

            case 1: {
                int opcion2;
                cout << "\n  -- Complemento a 1 --" << endl;
                cout << "  1. Desde decimal" << endl;
                cout << "  2. Desde binario" << endl;
                cout << "  Opcion: ";
                cin >> opcion2;

                if(opcion2 == 1){
                    int n, bits;
                    cout << "  Decimal: ";
                    cin >> n;
                    if(n < 0){ n = -n; }
                    cout << "  Bits: ";
                    cin >> bits;
                    string bin = decimalAAbinario(n);
                    if(bin.length() > bits){
                        cout << "  Error: el numero no cabe en " << bits << " bits." << endl;
                        break;
                    }
                    bin = ajustarBits(bin, bits);
                    cout << "  Binario        : " << bin << endl;
                    cout << "  Complemento a 1: " << complementoA1(bin) << endl;
                } else if(opcion2 == 2){
                    string bin;
                    cout << "  Binario: ";
                    cin >> bin;
                    cout << "  Complemento a 1: " << complementoA1(bin) << endl;
                }
                break;
            }

            case 2: {
                int opcion2;
                cout << "\n  -- Complemento a 2 --" << endl;
                cout << "  1. Desde decimal" << endl;
                cout << "  2. Desde binario" << endl;
                cout << "  Opcion: ";
                cin >> opcion2;

                if(opcion2 == 1){
                    int n, bits;
                    cout << "  Decimal: ";
                    cin >> n;
                    bool neg = (n < 0);
                    if(neg) n = -n;
                    cout << "  Bits: ";
                    cin >> bits;
                    string bin = decimalAAbinario(n);
                    if(bin.length() > bits){
                        cout << "  Error: el numero no cabe en " << bits << " bits." << endl;
                        break;
                    }
                    bin = ajustarBits(bin, bits);
                    cout << "  Binario        : " << bin << endl;
                    cout << "  Complemento a 2: " << complementoA2(bin) << endl;
                } else if(opcion2 == 2){
                    string bin;
                    cout << "  Binario: ";
                    cin >> bin;
                    cout << "  Complemento a 2: " << complementoA2(bin) << endl;
                }
                break;
            }

            case 3: {
                int num, bits;
                cout << "\n  -- Signo-Magnitud --" << endl;
                cout << "  Decimal: ";
                cin >> num;
                cout << "  Bits: ";
                cin >> bits;
                mostrarRangoSignoMagnitud(bits);
                int maximo = (1 << (bits - 1)) - 1;
                if(num < -maximo || num > maximo){
                    cout << "  Error: el numero no cabe en " << bits << " bits." << endl;
                    break;
                }
                cout << "  Signo-Magnitud: " << signoMagnitud(num, bits) << endl;
                break;
            }

            case 4: {
                int bits, num1, num2;
                cout << "\n  -- Suma sin signo --" << endl;
                cout << "  Numero 1: ";  cin >> num1;
                cout << "  Numero 2: ";  cin >> num2;
                cout << "  Bits: ";      cin >> bits;
                string bin1 = decimalAAbinario(num1);
                string bin2 = decimalAAbinario(num2);
                if(bin1.length() > bits || bin2.length() > bits){
                    cout << "  Error: alguno de los numeros no cabe en " << bits << " bits." << endl;
                    break;
                }
                bin1 = ajustarBits(bin1, bits);
                bin2 = ajustarBits(bin2, bits);
                cout << "  Binario 1: " << bin1 << endl;
                cout << "  Binario 2: " << bin2 << endl;
                cout << "  Suma     : " << sumaSinSigno(bin1, bin2) << endl;
                break;
            }

            case 5: {
                int num1, num2, bits;
                cout << "\n  -- Suma con signo (Complemento a 2) --" << endl;
                cout << "  Numero 1: ";  cin >> num1;
                cout << "  Numero 2: ";  cin >> num2;
                cout << "  Bits: ";      cin >> bits;
                mostrarRangoComplemento2(bits);
                if(!estaEnRangoComplemento2(num1, bits) || !estaEnRangoComplemento2(num2, bits)){
                    cout << "  Error: alguno de los numeros no cabe en " << bits << " bits." << endl;
                    break;
                }
                string bin1    = decimalAComplemento2(num1, bits);
                string bin2    = decimalAComplemento2(num2, bits);
                string resultado = sumaConSigno(num1, num2, bits);
                cout << "  Numero 1: " << bin1     << endl;
                cout << "  Numero 2: " << bin2     << endl;
                cout << "  Suma    : " << resultado << endl;
                if(!estaEnRangoComplemento2(num1 + num2, bits)){
                    cout << "  Advertencia: Overflow." << endl;
                }
                break;
            }

            case 6: {
                int num1, num2, bits;
                cout << "\n  -- Multiplicacion sin signo --" << endl;
                cout << "  Multiplicando: ";  cin >> num1;
                cout << "  Multiplicador: ";  cin >> num2;
                cout << "  Bits: ";           cin >> bits;
                int maximo = (1 << bits) - 1;
                cout << "  Rango permitido: [0, " << maximo << "]" << endl;
                if(num1 < 0 || num2 < 0 || num1 > maximo || num2 > maximo){
                    cout << "  Error: los numeros no caben en " << bits << " bits." << endl;
                    break;
                }
                string M = ajustarBits(decimalAAbinario(num1), bits);
                string Q = ajustarBits(decimalAAbinario(num2), bits);
                cout << "  M         = " << M << endl;
                cout << "  Q         = " << Q << endl;
                cout << "  Resultado = " << multiplicacionSinSigno(M, Q, bits) << endl;
                break;
            }

            case 7: {
                int num1, num2, bits;
                cout << "\n  -- Multiplicacion con signo (Booth) --" << endl;
                cout << "  Multiplicando: ";  cin >> num1;
                cout << "  Multiplicador: ";  cin >> num2;
                cout << "  Bits: ";           cin >> bits;
                mostrarRangoComplemento2(bits);
                if(!estaEnRangoComplemento2(num1, bits) || !estaEnRangoComplemento2(num2, bits)){
                    cout << "  Error: alguno de los numeros no cabe en " << bits << " bits." << endl;
                    break;
                }
                string resultado = multiplicacionBooth(num1, num2, bits);
                cout << "  Resultado binario = " << resultado << endl;
                cout << "  Resultado decimal = " << complemento2ADecimal(resultado) << endl;
                long long producto = (long long)num1 * num2;
                long long minimo   = -(1LL << (2 * bits - 1));
                long long maximo   =  (1LL << (2 * bits - 1)) - 1;
                if(producto < minimo || producto > maximo){
                    cout << "  Advertencia: Overflow." << endl;
                }
                break;
            }

            case 8: {
                int dividendo, divisor, bits;
                cout << "\n  -- Division sin signo --" << endl;
                cout << "  Dividendo: ";  cin >> dividendo;
                cout << "  Divisor  : ";  cin >> divisor;
                cout << "  Bits: ";       cin >> bits;
                int maximo = (1 << bits) - 1;
                cout << "  Rango permitido: [0, " << maximo << "]" << endl;
                if(dividendo < 0 || divisor < 0){
                    cout << "  Error: solo acepta numeros positivos." << endl;
                    break;
                }
                if(dividendo > maximo || divisor > maximo){
                    cout << "  Error: los numeros no caben en " << bits << " bits." << endl;
                    break;
                }
                divisionSinSigno(dividendo, divisor, bits);
                break;
            }

            case 9: {
                double numero;
                cout << "\n  -- Representacion en Coma Flotante --" << endl;
                cout << "  Numero decimal: ";
                cin >> numero;
                representacionComaFlotante(numero);
                break;
            }

            case 10:
                cout << "\n  Programa finalizado." << endl;
                separador();
                break;

            default:
                cout << "\n  Opcion invalida." << endl;
        }

    } while(opcion != 10);

    return 0;
}
