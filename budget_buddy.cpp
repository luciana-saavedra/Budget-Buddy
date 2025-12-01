// ========== Budget Buddy ==========

// ----------------------- LIBRERÍAS ---------------------
# include <iostream>
# include <vector>
# include <cstring>
# include <fstream>
# include <iomanip>
# include <limits>
# include <algorithm>
# include <cstdlib>

// ----------------------- NAMESPACE Y ARCHIVO ----------------------
using namespace std;
const string nombre_archivo = "gastos.csv";
// ----------------------- ESTRUCTURAS --------------------
struct Gasto {
    double monto;
    char categoria[20];
    char fecha[12];
    char descripcion[50];
};

// ----------------------- FUNCIONES ----------------------
void borrar_pantalla() {
    system("cls");
}

// ----------------------- FUNCIONES CSV ------------------
void cargar_csv(vector<Gasto>& gastos) {
    ifstream archivo(nombre_archivo);
    // --------------------------------
    if (!archivo.is_open()) {
        cout << "\nNo se pudo abrir el archivo CSV. Se creara posteriormente. " << nombre_archivo;
        return;
    }
    // ---------------------------------
    char linea[256]; 
    archivo.getline(linea, sizeof(linea)); 
    // ---------------------------------
    while (archivo.getline(linea, sizeof(linea))) {
        if (linea[0] =='\0')
            continue; 
        char* p1 = strchr(linea, ',');
        if (!p1) 
            continue;
        char* p2 = strchr(p1 + 1, ',');
        if (!p2)
            continue;
        char* p3 = strchr(p2 + 1, ',');
        if (!p3)
            continue;
        // ---------------------------------
        char campo_monto[20];
        char campo_categoria[20];
        char campo_fecha[12];
        char campo_desc[60];
        // ---------------------------------
        int len1=p1-linea;
        strncpy(campo_monto, linea, len1);
        campo_monto[len1]='\0';
        int len2=p2-(p1+1);
        strncpy(campo_categoria, p1+1, len1);
        campo_categoria[len2]='\0';
        int len3=p3-(p2+1);
        strncpy(campo_fecha, p2+1, len1);
        campo_fecha[len3]='\0';
        strcpy(campo_desc, p3+1);
        // ---------------------------------
        Gasto g;
        g.monto = atof(campo_monto);
        strncpy(g.categoria, campo_categoria, sizeof(g.categoria)-1);
        g.categoria[sizeof(g.categoria)-1] = '\0';
        strncpy(g.fecha, campo_fecha, sizeof(g.fecha)-1);
        g.fecha[sizeof(g.fecha)-1] = '\0';
        strncpy(g.descripcion, campo_desc, sizeof(g.descripcion)-1);
        g.descripcion[sizeof(g.descripcion)-1] = '\0';
        // ---------------------------------
        gastos.push_back(g);
    }
    archivo.close();
}
// --------------------------------------------------------

void guardarCSV(const vector<Gasto>& gastos) {
    ofstream archivo(nombre_archivo.c_str());
    if (!archivo.is_open()) {
        cout << "\nError writing CSV.";
        return;
    }
    // ---------------------------------
    archivo << "monto,categoria,fecha,descripcion\n";
    // ---------------------------------
    for (const auto& g : gastos) {
        archivo<<g.monto<<","
                <<g.categoria<<","
                <<g.fecha<<","
                <<g.descripcion<<"\n";
    }
    // ---------------------------------
    archivo.close();
}