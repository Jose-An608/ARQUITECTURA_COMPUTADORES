#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>

using namespace std;

/* ---- Registros de la CPU ---- */
struct CPU {
    int PC  = 0;
    int AC  = 0;
    int IR  = 0;
    int MBR = 0;
    int MAR = 0;
};

/* ---- Memoria principal ---- */
map<int, int> memoria;

/* ---- Convierte entero a hex de 4 digitos ---- */
string toHex4(int v) {
    ostringstream ss;
    ss << uppercase << hex << setw(4) << setfill('0') << (v & 0xFFFF);
    return ss.str();
}

/* ---- Convierte a binario de 16 bits ---- */
string hexToBin16(int valor) {
    string bits = "";
    for (int i = 15; i >= 0; i--) {
        bits += ((valor >> i) & 1) ? "1" : "0";
        if (i % 4 == 0 && i != 0) bits += " ";
    }
    return bits;
}

/* ---- Mostrar registros ---- */
void mostrarRegistros(const CPU& cpu) {
    cout << "  +------------+--------+\n";
    cout << "  |  Registro  | Valor  |\n";
    cout << "  +------------+--------+\n";
    cout << "  |     PC     |  " << toHex4(cpu.PC)  << "  |\n";
    cout << "  |     AC     |  " << toHex4(cpu.AC)  << "  |\n";
    cout << "  |     IR     |  " << toHex4(cpu.IR)  << "  |\n";
    cout << "  |     MBR    |  " << toHex4(cpu.MBR) << "  |\n";
    cout << "  |     MAR    |  " << toHex4(cpu.MAR) << "  |\n";
    cout << "  +------------+--------+\n";
}

/* ---- Decodificar ---- */
string decodificar(int codop, int operando) {
    switch (codop) {
        case 0x1: return "Cargar AC desde direccion " + toHex4(operando);
        case 0x2: return "Sumar MEM[" + toHex4(operando) + "] al AC";
        case 0x3: return "Restar MEM[" + toHex4(operando) + "] del AC";
        case 0x4: return "Almacenar AC en direccion " + toHex4(operando);
        default:  return "CODOP desconocido - sin operacion";
    }
}

/* ---- Separador ---- */
void separador(const string& titulo) {
    cout << "\n==================================================\n";
    cout << "  " << titulo << "\n";
    cout << "==================================================\n";
}

/* ---- CICLO ---- */
void ciclo(CPU& cpu, int direccion) {

    separador("CAPTACION  --  PC = " + toHex4(direccion));

    cpu.PC  = direccion;
    cpu.MAR = cpu.PC;
    cpu.MBR = memoria[cpu.MAR];
    cpu.IR  = cpu.MBR;

    cout << "  > El PC apunta a la direccion: " << toHex4(cpu.PC) << "\n";
    cout << "  > MAR <- PC          = " << toHex4(cpu.MAR) << "\n";
    cout << "  > MBR <- MEM[" << toHex4(cpu.MAR) << "] = " << toHex4(cpu.MBR) << "\n";
    cout << "  > IR  <- MBR         = " << toHex4(cpu.IR)  << "\n";

    cout << "\n  Representacion binaria de IR:\n";
    cout << "  " << hexToBin16(cpu.IR) << "\n";

    cout << "\n  Estado de registros tras CAPTACION:\n";
    mostrarRegistros(cpu);

    separador("EJECUCION  --  PC = " + toHex4(direccion));

    int codop    = (cpu.IR >> 12) & 0xF;
    int operando =  cpu.IR & 0x0FFF;

    cout << "  CODOP    = " << codop << " (0b";
    for (int i = 3; i >= 0; i--) cout << ((codop >> i) & 1);
    cout << ")\n";

    cout << "  Operando = " << toHex4(operando) << "\n";

    cout << "\n  Instruccion: " << decodificar(codop, operando) << "\n";

    bool ok = true;

    switch (codop) {
        case 0x1:
            cpu.MAR = operando;
            cpu.MBR = memoria[cpu.MAR];
            cpu.AC  = cpu.MBR;
            cout << "  AC <- MEM[" << toHex4(operando) << "] = " << toHex4(cpu.AC) << "\n";
            break;

        case 0x2:
            cpu.MAR = operando;
            cpu.MBR = memoria[cpu.MAR];
            cout << "  AC (" << toHex4(cpu.AC) << ") + MEM[" 
                 << toHex4(operando) << "] (" << toHex4(cpu.MBR) << ") = ";
            cpu.AC = (cpu.AC + cpu.MBR) & 0xFFFF;
            cout << toHex4(cpu.AC) << "\n";
            break;

        case 0x3:
            cpu.MAR = operando;
            cpu.MBR = memoria[cpu.MAR];
            cout << "  AC (" << toHex4(cpu.AC) << ") - MEM[" 
                 << toHex4(operando) << "] (" << toHex4(cpu.MBR) << ") = ";
            cpu.AC = (cpu.AC - cpu.MBR) & 0xFFFF;
            cout << toHex4(cpu.AC) << "\n";
            break;

        case 0x4:
            cpu.MAR = operando;
            cpu.MBR = cpu.AC;
            memoria[cpu.MAR] = cpu.MBR;
            cout << "  MEM[" << toHex4(operando) << "] <- AC = " << toHex4(cpu.AC) << "\n";
            break;

        default:
            cout << "  CODOP no definido.\n";
            ok = false;
            break;
    }

    if (ok)
        cout << "\n  Estado de registros tras EJECUCION:\n";
    else
        cout << "\n  Registros sin cambio:\n";

    mostrarRegistros(cpu);
}

/* ---- MAIN ---- */
int main() {

    cout << "\nSIMULADOR DE CAPTACION Y EJECUCION\n";

    memoria[0x501] = 0x1601;
    memoria[0x502] = 0x2603;
    memoria[0x503] = 0x3604;
    memoria[0x504] = 0x4601;

    memoria[0x601] = 0x0005;
    memoria[0x602] = 0x0002;
    memoria[0x603] = 0x0004;
    memoria[0x604] = 0x0003;

    CPU cpu;
    cpu.AC = 0x0000;

    int dirs[] = {0x501, 0x502, 0x503, 0x504};

    for (int i = 0; i < 4; i++) {
        ciclo(cpu, dirs[i]);
        cout << "\n";
    }

    cout << "\nProceso finalizado.\n";

    return 0;
}
