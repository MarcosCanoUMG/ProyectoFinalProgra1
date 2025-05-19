//PROGRAMADORES:
//Marcos Eduardo Cano Méndez 2590-24-3996
//Diego Antonio Villatoro Escobar 2590-24-7262
//Brandon Isaac Gómez 2590-24-8845
//Emanuel Bonifacio García Tzoc 2590-24-1555

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

// Estructuras de datos
struct Cliente {
    int dpi =0;
    int telefono = 0;
    char nombre[25] = "";
    char apellidos[25] = "";
    char correo[50] = "";
    char direccion[100] = "";
};

struct Vehiculo {
    char placa[15] = "";
    char modelo[25] = "";
    char marca[25] = "";
    int anio = 0;
    char color[20] = "";
    char noSerie[30] = "";
};

struct Trabajador {
    int id = 0;
    char nombre[25] = "";
    char apellidos[25] = "";
    char puesto[30] = "";
    float salario = 0;
    char telefono[15] = "";
};

struct Cita {
    int id = 0;
    int idCliente = 0;
    int idTrabajador = 0;
    char placaVehiculo[15] = "";
    char fecha[20] = "";
    char hora[10] = "";
    char descripcion[200] = "";
    char estado[20] = "Pendiente";
};




// Vehiculos
void CrearVehiculo() {
    Vehiculo v;
    cin.ignore();
    try {
        cout << "Ingrese la placa del vehiculo: ";
        cin.getline(v.placa, 15);
        if (strlen(v.placa) == 0) throw runtime_error("La placa no puede estar vacía.");

        cout << "Ingrese el modelo del vehiculo: ";
        cin.getline(v.modelo, 25);
        if (strlen(v.modelo) == 0) throw runtime_error("El modelo no puede estar vacío.");

        cout << "Ingrese la marca del vehiculo: ";
        cin.getline(v.marca, 25);
        if (strlen(v.marca) == 0) throw runtime_error("La marca no puede estar vacía.");

        cout << "Ingrese el año del vehiculo: ";
        if (!(cin >> v.anio)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        cout << "Ingrese el color del vehiculo: ";
        cin.getline(v.color, 20);
        if (strlen(v.color) == 0) throw runtime_error("El color no puede estar vacío.");

        cout << "Ingrese el número de serie del vehiculo: ";
        cin.getline(v.noSerie, 30);
        if (strlen(v.noSerie) == 0) throw runtime_error("El número de serie no puede estar vacío.");

        ofstream f("vehiculos.bin", ios::binary | ios::app);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");
        f.write((char*)&v, sizeof(Vehiculo));
        f.close();
        cout << "Vehículo registrado exitosamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void LeerVehiculo() {
    Vehiculo v;
    try {
        ifstream f("vehiculos.bin", ios::binary);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");

        while (f.read((char*)&v, sizeof(Vehiculo))) {
            cout << "Placa: " << v.placa << endl;
            cout << "Modelo: " << v.modelo << endl;
            cout << "Marca: " << v.marca << endl;
            cout << "Anio: " << v.anio << endl;
            cout << "Color: " << v.color << endl;
            cout << "Número de serie: " << v.noSerie << endl;
            cout << "------------------------" << endl;
        }
        f.close();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void EditarVehiculo() {
    Vehiculo v;
    char placaBuscada[15];
    bool encontrado = false;

    try {
        cout << "Ingrese la placa del vehiculo a editar: ";
        cin.ignore();
        cin.getline(placaBuscada, 15);

        ifstream aOrigen("vehiculos.bin", ios::binary);
        ofstream aTemporal("vehiculostemp.bin", ios::binary);
        if (!aOrigen.is_open() || !aTemporal.is_open()) throw runtime_error("No se pudo abrir el archivo.");

        while (aOrigen.read((char*)&v, sizeof(Vehiculo))) {
            if (strcmp(v.placa, placaBuscada) == 0) {
                encontrado = true;
                cout << "Ingrese nuevo modelo: ";
                cin.getline(v.modelo, 25);
                if (strlen(v.modelo) == 0) throw runtime_error("El modelo no puede estar vacío.");

                cout << "Ingrese nueva marca: ";
                cin.getline(v.marca, 25);
                if (strlen(v.marca) == 0) throw runtime_error("La marca no puede estar vacía.");

                cout << "Ingrese nuevo anio: ";
                if (!(cin >> v.anio)) throw runtime_error("Debe ingresar un número válido.");
                cin.ignore();

                cout << "Ingrese nuevo color: ";
                cin.getline(v.color, 20);
                if (strlen(v.color) == 0) throw runtime_error("El color no puede estar vacío.");

                cout << "Ingrese nuevo número de serie: ";
                cin.getline(v.noSerie, 30);
                if (strlen(v.noSerie) == 0) throw runtime_error("El número de serie no puede estar vacío.");
            }
            aTemporal.write((char*)&v, sizeof(Vehiculo));
        }
        aOrigen.close();
        aTemporal.close();

        if (!encontrado) throw runtime_error("Vehículo no encontrado.");
        remove("vehiculos.bin");
        rename("vehiculostemp.bin", "vehiculos.bin");
        cout << "El vehículo ha sido modificado correctamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void BuscarVehiculo() {
    Vehiculo v;
    char placaBuscada[15];
    bool encontrado = false;

    try {
        cout << "Ingrese la placa del vehiculo a buscar: ";
        cin.ignore();
        cin.getline(placaBuscada, 15);

        ifstream f("vehiculos.bin", ios::binary);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");

        while (f.read((char*)&v, sizeof(Vehiculo))) {
            if (strcmp(v.placa, placaBuscada) == 0) {
                encontrado = true;
                cout << "Placa: " << v.placa << endl;
                cout << "Modelo: " << v.modelo << endl;
                cout << "Marca: " << v.marca << endl;
                cout << "Anio: " << v.anio << endl;
                cout << "Color: " << v.color << endl;
                cout << "Número de serie: " << v.noSerie << endl;
                cout << "------------------------" << endl;
                break;
            }
        }
        f.close();
        if (!encontrado) throw runtime_error("Vehículo no encontrado.");
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void EliminarVehiculo() {
    Vehiculo v;
    char placaEliminar[15];
    bool encontrado = false;

    try {
        cout << "Ingrese la placa del vehiculo a eliminar: ";
        cin.ignore();
        cin.getline(placaEliminar, 15);

        ifstream aOrigen("vehiculos.bin", ios::binary);
        ofstream aTemporal("vehiculostemp.bin", ios::binary);
        if (!aOrigen.is_open() || !aTemporal.is_open()) throw runtime_error("No se pudo abrir el archivo.");

        while (aOrigen.read((char*)&v, sizeof(Vehiculo))) {
            if (strcmp(v.placa, placaEliminar) != 0) {
                aTemporal.write((char*)&v, sizeof(Vehiculo));
            } else {
                encontrado = true;
            }
        }
        aOrigen.close();
        aTemporal.close();

        remove("vehiculos.bin");
        rename("vehiculostemp.bin", "vehiculos.bin");
        if (!encontrado) throw runtime_error("Vehículo no encontrado.");
        cout << "El vehículo ha sido eliminado correctamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

// TRABAJADORES
void CrearTrabajador() {
    Trabajador t;
    cin.ignore();
    try {
        cout << "Ingrese el ID del trabajador: ";
        if (!(cin >> t.id)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        cout << "Ingrese el nombre del trabajador: ";
        cin.getline(t.nombre, 25);
        if (strlen(t.nombre) == 0) throw runtime_error("El nombre no puede estar vacío.");

        cout << "Ingrese los apellidos del trabajador: ";
        cin.getline(t.apellidos, 25);
        if (strlen(t.apellidos) == 0) throw runtime_error("Los apellidos no pueden estar vacíos.");

        cout << "Ingrese el puesto del trabajador: ";
        cin.getline(t.puesto, 30);
        if (strlen(t.puesto) == 0) throw runtime_error("El puesto no puede estar vacío.");

        cout << "Ingrese el salario del trabajador: ";
        if (!(cin >> t.salario)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        cout << "Ingrese el teléfono del trabajador: ";
        cin.getline(t.telefono, 15);
        if (strlen(t.telefono) == 0) throw runtime_error("El teléfono no puede estar vacío.");

        ofstream f("trabajadores.bin", ios::binary | ios::app);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");
        f.write((char*)&t, sizeof(Trabajador));
        f.close();
        cout << "Trabajador registrado exitosamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void LeerTrabajador() {
    Trabajador t;
    try {
        ifstream f("trabajadores.bin", ios::binary);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");

        while (f.read((char*)&t, sizeof(Trabajador))) {
            cout << "ID: " << t.id << endl;
            cout << "Nombre: " << t.nombre << endl;
            cout << "Apellidos: " << t.apellidos << endl;
            cout << "Puesto: " << t.puesto << endl;
            cout << "Salario: " << t.salario << endl;
            cout << "Teléfono: " << t.telefono << endl;
            cout << "------------------------" << endl;
        }
        f.close();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void EditarTrabajador() {
    Trabajador t;
    int idBuscado;
    bool encontrado = false;

    try {
        cout << "Ingrese el ID del trabajador a editar: ";
        if (!(cin >> idBuscado)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        ifstream aOrigen("trabajadores.bin", ios::binary);
        ofstream aTemporal("trabajadorestemp.bin", ios::binary);
        if (!aOrigen.is_open() || !aTemporal.is_open()) throw runtime_error("No se pudo abrir el archivo.");

        while (aOrigen.read((char*)&t, sizeof(Trabajador))) {
            if (t.id == idBuscado) {
                encontrado = true;
                cout << "Ingrese nuevo nombre: ";
                cin.getline(t.nombre, 25);
                if (strlen(t.nombre) == 0) throw runtime_error("El nombre no puede estar vacío.");

                cout << "Ingrese nuevos apellidos: ";
                cin.getline(t.apellidos, 25);
                if (strlen(t.apellidos) == 0) throw runtime_error("Los apellidos no pueden estar vacíos.");

                cout << "Ingrese nuevo puesto: ";
                cin.getline(t.puesto, 30);
                if (strlen(t.puesto) == 0) throw runtime_error("El puesto no puede estar vacío.");

                cout << "Ingrese nuevo salario: ";
                if (!(cin >> t.salario)) throw runtime_error("Debe ingresar un número válido.");
                cin.ignore();

                cout << "Ingrese nuevo teléfono: ";
                cin.getline(t.telefono, 15);
                if (strlen(t.telefono) == 0) throw runtime_error("El teléfono no puede estar vacío.");
            }
            aTemporal.write((char*)&t, sizeof(Trabajador));
        }
        aOrigen.close();
        aTemporal.close();

        if (!encontrado) throw runtime_error("Trabajador no encontrado.");
        remove("trabajadores.bin");
        rename("trabajadorestemp.bin", "trabajadores.bin");
        cout << "El trabajador ha sido modificado correctamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void BuscarTrabajador() {
    Trabajador t;
    int idBuscado;
    bool encontrado = false;

    try {
        cout << "Ingrese el ID del trabajador a buscar: ";
        if (!(cin >> idBuscado)) throw runtime_error("Debe ingresar un número válido.");

        ifstream f("trabajadores.bin", ios::binary);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");

        while (f.read((char*)&t, sizeof(Trabajador))) {
            if (t.id == idBuscado) {
                encontrado = true;
                cout << "ID: " << t.id << endl;
                cout << "Nombre: " << t.nombre << endl;
                cout << "Apellidos: " << t.apellidos << endl;
                cout << "Puesto: " << t.puesto << endl;
                cout << "Salario: " << t.salario << endl;
                cout << "Teléfono: " << t.telefono << endl;
                cout << "------------------------" << endl;
                break;
            }
        }
        f.close();
        if (!encontrado) throw runtime_error("Trabajador no encontrado.");
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void EliminarTrabajador() {
    Trabajador t;
    int idEliminar;
    bool encontrado = false;

    try {
        cout << "Ingrese el ID del trabajador a eliminar: ";
        if (!(cin >> idEliminar)) throw runtime_error("Debe ingresar un número válido.");

        ifstream aOrigen("trabajadores.bin", ios::binary);
        ofstream aTemporal("trabajadorestemp.bin", ios::binary);
        if (!aOrigen.is_open() || !aTemporal.is_open()) throw runtime_error("No se pudo abrir el archivo.");

        while (aOrigen.read((char*)&t, sizeof(Trabajador))) {
            if (t.id != idEliminar) {
                aTemporal.write((char*)&t, sizeof(Trabajador));
            } else {
                encontrado = true;
            }
        }
        aOrigen.close();
        aTemporal.close();

        remove("trabajadores.bin");
        rename("trabajadorestemp.bin", "trabajadores.bin");
        if (!encontrado) throw runtime_error("Trabajador no encontrado.");
        cout << "El trabajador ha sido eliminado correctamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}
// CLIENTES
void CrearCliente() {
    Cliente c;
    cin.ignore();
    try {
        cout << "Ingrese el DPI del cliente: ";
        if (!(cin >> c.dpi)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        cout << "Ingrese el nombre del cliente: ";
        cin.getline(c.nombre, 25);
        if (strlen(c.nombre) == 0) throw runtime_error("El nombre no puede estar vacío.");

        cout << "Ingrese los apellidos del cliente: ";
        cin.getline(c.apellidos, 25);
        if (strlen(c.apellidos) == 0) throw runtime_error("Los apellidos no pueden estar vacíos.");

        cout << "Ingrese el teléfono del cliente: ";
        if (!(cin >> c.telefono)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        cout << "Ingrese el correo del cliente: ";
        cin.getline(c.correo, 50);
        if (strlen(c.correo) == 0) throw runtime_error("El correo no puede estar vacío.");

        cout << "Ingrese la dirección del cliente: ";
        cin.getline(c.direccion, 100);
        if (strlen(c.direccion) == 0) throw runtime_error("La dirección no puede estar vacía.");

        ofstream f("clientes.bin", ios::binary | ios::app);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");
        f.write((char*)&c, sizeof(Cliente));
        f.close();
        cout << "Cliente registrado exitosamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void LeerCliente() {
    Cliente c;
    try {
        ifstream f("clientes.bin", ios::binary);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");

        while (f.read((char*)&c, sizeof(Cliente))) {
            cout << "DPI: " << c.dpi << endl;
            cout << "Nombre: " << c.nombre << endl;
            cout << "Apellidos: " << c.apellidos << endl;
            cout << "Teléfono: " << c.telefono << endl;
            cout << "Correo: " << c.correo << endl;
            cout << "Dirección: " << c.direccion << endl;
            cout << "------------------------" << endl;
        }
        f.close();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void EditarCliente() {
    Cliente c;
    int dpibuscado;
    bool encontrado = false;

    try {
        cout << "Ingrese el DPI del cliente a editar: ";
        if (!(cin >> dpibuscado)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        ifstream aOrigen("clientes.bin", ios::binary);
        ofstream aTemporal("clientestemp.bin", ios::binary);
        if (!aOrigen.is_open() || !aTemporal.is_open()) throw runtime_error("No se pudo abrir el archivo.");

        while (aOrigen.read((char*)&c, sizeof(Cliente))) {
            if (c.dpi == dpibuscado) {
                encontrado = true;
                cout << "Ingrese nuevo nombre: ";
                cin.getline(c.nombre, 25);
                if (strlen(c.nombre) == 0) throw runtime_error("El nombre no puede estar vacío.");

                cout << "Ingrese nuevos apellidos: ";
                cin.getline(c.apellidos, 25);
                if (strlen(c.apellidos) == 0) throw runtime_error("Los apellidos no pueden estar vacíos.");

                cout << "Ingrese el teléfono del cliente: ";
                if (!(cin >> c.telefono)) throw runtime_error("Debe ingresar un número válido.");
                cin.ignore();


                cout << "Ingrese nuevo correo: ";
                cin.getline(c.correo, 50);
                if (strlen(c.correo) == 0) throw runtime_error("El correo no puede estar vacío.");

                cout << "Ingrese nueva dirección: ";
                cin.getline(c.direccion, 100);
                if (strlen(c.direccion) == 0) throw runtime_error("La dirección no puede estar vacía.");
            }
            aTemporal.write((char*)&c, sizeof(Cliente));  // Cambiado de Trabajador a Contacto
        }
        aOrigen.close();
        aTemporal.close();

        if (!encontrado) throw runtime_error("Cliente no encontrado.");
        remove("clientes.bin");
        rename("clientestemp.bin", "clientes.bin");
        cout << "El cliente ha sido modificado correctamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void BuscarCliente() {
    Cliente c;
    int dpibuscado;
    bool encontrado = false;

    try {
        cout << "Ingrese el DPI del cliente a buscar: ";
        if (!(cin >> dpibuscado)) throw runtime_error("Debe ingresar un número válido.");

        ifstream f("clientes.bin", ios::binary);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");

        while (f.read((char*)&c, sizeof(Cliente))) {
            if (c.dpi == dpibuscado) {
                encontrado = true;
                cout << "Teléfono: " << c.telefono << endl;
                cout << "Nombre: " << c.nombre << endl;
                cout << "Apellidos: " << c.apellidos << endl;
                cout << "Correo: " << c.correo << endl;
                cout << "Dirección: " << c.direccion << endl;
                cout << "------------------------" << endl;
                break;
            }
        }
        f.close();
        if (!encontrado) throw runtime_error("Cliente no encontrado.");
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void EliminarCliente() {
    Cliente c;
    int dpibuscado;
    bool encontrado = false;

    try {
        cout << "Ingrese el DPI del cliente a eliminar: ";
        if (!(cin >> dpibuscado)) throw runtime_error("Debe ingresar un número válido.");

        ifstream aOrigen("clientes.bin", ios::binary);
        ofstream aTemporal("clientestemp.bin", ios::binary);
        if (!aOrigen.is_open() || !aTemporal.is_open()) throw runtime_error("No se pudo abrir el archivo.");

        while (aOrigen.read((char*)&c, sizeof(Cliente))) {
            if (c.dpi != dpibuscado) {
                aTemporal.write((char*)&c, sizeof(Cliente));
            } else {
                encontrado = true;
            }
        }
        aOrigen.close();
        aTemporal.close();

        remove("clientes.bin");
        rename("clientestemp.bin", "clientes.bin");
        if (!encontrado) throw runtime_error("Cliente no encontrado.");
        cout << "El cliente ha sido eliminado correctamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

// CITAS
void CrearCita() {
    Cita c;
    cin.ignore();
    try {
        cout << "Ingrese el ID de la cita: ";
        if (!(cin >> c.id)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        cout << "Ingrese el DPI del cliente: ";
        if (!(cin >> c.idCliente)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        cout << "Ingrese el ID del trabajador: ";
        if (!(cin >> c.idTrabajador)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        cout << "Ingrese la placa del vehículo: ";
        cin.getline(c.placaVehiculo, 15);
        if (strlen(c.placaVehiculo) == 0) throw runtime_error("La placa no puede estar vacía.");

        cout << "Ingrese la fecha (DD/MM/AAAA): ";
        cin.getline(c.fecha, 20);
        if (strlen(c.fecha) == 0) throw runtime_error("La fecha no puede estar vacía.");

        cout << "Ingrese la hora (HH:MM): ";
        cin.getline(c.hora, 10);
        if (strlen(c.hora) == 0) throw runtime_error("La hora no puede estar vacía.");

        cout << "Ingrese la descripción del servicio: ";
        cin.getline(c.descripcion, 200);
        if (strlen(c.descripcion) == 0) throw runtime_error("La descripción no puede estar vacía.");

        ofstream f("citas.bin", ios::binary | ios::app);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");
        f.write((char*)&c, sizeof(Cita));
        f.close();
        cout << "Cita creada exitosamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void LeerCita() {
    Cita c;
    try {
        ifstream f("citas.bin", ios::binary);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");

        while (f.read((char*)&c, sizeof(Cita))) {
            cout << "ID Cita: " << c.id << endl;
            cout << "DPI Cliente: " << c.idCliente << endl;
            cout << "ID Trabajador: " << c.idTrabajador << endl;
            cout << "Placa Vehículo: " << c.placaVehiculo << endl;
            cout << "Fecha: " << c.fecha << endl;
            cout << "Hora: " << c.hora << endl;
            cout << "Descripción: " << c.descripcion << endl;
            cout << "Estado: " << c.estado << endl;
            cout << "------------------------" << endl;
        }
        f.close();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void EditarCita() {
    Cita c;
    int idBuscado;
    bool encontrado = false;

    try {
        cout << "Ingrese el ID de la cita a editar: ";
        if (!(cin >> idBuscado)) throw runtime_error("Debe ingresar un número válido.");
        cin.ignore();

        ifstream aOrigen("citas.bin", ios::binary);
        ofstream aTemporal("citastemp.bin", ios::binary);
        if (!aOrigen.is_open() || !aTemporal.is_open()) throw runtime_error("No se pudo abrir el archivo.");

        while (aOrigen.read((char*)&c, sizeof(Cita))) {
            if (c.id == idBuscado) {
                encontrado = true;
                cout << "Ingrese nuevo ID de cliente: ";
                if (!(cin >> c.idCliente)) throw runtime_error("Debe ingresar un número válido.");
                cin.ignore();

                cout << "Ingrese nuevo ID de trabajador: ";
                if (!(cin >> c.idTrabajador)) throw runtime_error("Debe ingresar un número válido.");
                cin.ignore();

                cout << "Ingrese nueva placa de vehículo: ";
                cin.getline(c.placaVehiculo, 15);
                if (strlen(c.placaVehiculo) == 0) throw runtime_error("La placa no puede estar vacía.");

                cout << "Ingrese nueva fecha (DD/MM/AAAA): ";
                cin.getline(c.fecha, 20);
                if (strlen(c.fecha) == 0) throw runtime_error("La fecha no puede estar vacía.");

                cout << "Ingrese nueva hora (HH:MM): ";
                cin.getline(c.hora, 10);
                if (strlen(c.hora) == 0) throw runtime_error("La hora no puede estar vacía.");

                cout << "Ingrese nueva descripción: ";
                cin.getline(c.descripcion, 200);
                if (strlen(c.descripcion) == 0) throw runtime_error("La descripción no puede estar vacía.");

                cout << "Ingrese nuevo estado: ";
                cin.getline(c.estado, 20);
                if (strlen(c.estado) == 0) throw runtime_error("El estado no puede estar vacío.");
            }
            aTemporal.write((char*)&c, sizeof(Cita));
        }
        aOrigen.close();
        aTemporal.close();

        if (!encontrado) throw runtime_error("Cita no encontrada.");
        remove("citas.bin");
        rename("citastemp.bin", "citas.bin");
        cout << "La cita ha sido modificada correctamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void BuscarCita() {
    Cita c;
    int idBuscado;
    bool encontrado = false;

    try {
        cout << "Ingrese el ID de la cita a buscar: ";
        if (!(cin >> idBuscado)) throw runtime_error("Debe ingresar un número válido.");

        ifstream f("citas.bin", ios::binary);
        if (!f.is_open()) throw runtime_error("Error de apertura de archivo.");

        while (f.read((char*)&c, sizeof(Cita))) {
            if (c.id == idBuscado) {
                encontrado = true;
                cout << "ID Cita: " << c.id << endl;
                cout << "ID Cliente: " << c.idCliente << endl;
                cout << "ID Trabajador: " << c.idTrabajador << endl;
                cout << "Placa Vehículo: " << c.placaVehiculo << endl;
                cout << "Fecha: " << c.fecha << endl;
                cout << "Hora: " << c.hora << endl;
                cout << "Descripción: " << c.descripcion << endl;
                cout << "Estado: " << c.estado << endl;
                cout << "------------------------" << endl;
                break;
            }
        }
        f.close();
        if (!encontrado) throw runtime_error("Cita no encontrada.");
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}

void EliminarCita() {
    Cita c;
    int idEliminar;
    bool encontrado = false;

    try {
        cout << "Ingrese el ID de la cita a eliminar: ";
        if (!(cin >> idEliminar)) throw runtime_error("Debe ingresar un número válido.");

        ifstream aOrigen("citas.bin", ios::binary);
        ofstream aTemporal("citastemp.bin", ios::binary);
        if (!aOrigen.is_open() || !aTemporal.is_open()) throw runtime_error("No se pudo abrir el archivo.");

        while (aOrigen.read((char*)&c, sizeof(Cita))) {
            if (c.id != idEliminar) {
                aTemporal.write((char*)&c, sizeof(Cita));
            } else {
                encontrado = true;
            }
        }
        aOrigen.close();
        aTemporal.close();

        remove("citas.bin");
        rename("citastemp.bin", "citas.bin");
        if (!encontrado) throw runtime_error("Cita no encontrada.");
        cout << "La cita ha sido eliminada correctamente." << endl;
    } catch (const exception& e) {
        cin.clear(); cin.ignore(10000, '\n');
        cerr << "Error: " << e.what() << endl;
    }
    cout << "_" << endl;
}


void menuClientes() {
    int opcion;
    do {
        cout << "\nGESTION DE CLIENTES" << endl;
        cout << "1. Crear Cliente" << endl;
        cout << "2. Mostrar Clientes" << endl;
        cout << "3. Editar Cliente" << endl;
        cout << "4. Buscar Cliente" << endl;
        cout << "5. Eliminar Cliente" << endl;
        cout << "6. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1: CrearCliente(); break;
            case 2: LeerCliente(); break;
            case 3: EditarCliente(); break;
            case 4: BuscarCliente(); break;
            case 5: EliminarCliente(); break;
            case 6: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion no valida." << endl; break;
        }
    } while (opcion != 6);
    system("cls");
}

void menuVehiculos() {
    int opcion;
    do {
        cout << "\nGESTION DE VEHICULOS" << endl;
        cout << "1. Registrar Vehiculo" << endl;
        cout << "2. Mostrar Vehiculos" << endl;
        cout << "3. Editar Vehiculo" << endl;
        cout << "4. Buscar Vehiculo" << endl;
        cout << "5. Eliminar Vehiculo" << endl;
        cout << "6. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1: CrearVehiculo(); break;
            case 2: LeerVehiculo(); break;
            case 3: EditarVehiculo(); break;
            case 4: BuscarVehiculo(); break;
            case 5: EliminarVehiculo(); break;
            case 6: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion no valida." << endl; break;
        }
    } while (opcion != 6);
    system("cls");
}

void menuTrabajadores() {
    int opcion;
    do {
        cout << "\nGESTION DE TRABAJADORES" << endl;
        cout << "1. Registrar Trabajador" << endl;
        cout << "2. Mostrar Trabajadores" << endl;
        cout << "3. Editar Trabajador" << endl;
        cout << "4. Buscar Trabajador" << endl;
        cout << "5. Eliminar Trabajador" << endl;
        cout << "6. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1: CrearTrabajador(); break;
            case 2: LeerTrabajador(); break;
            case 3: EditarTrabajador(); break;
            case 4: BuscarTrabajador(); break;
            case 5: EliminarTrabajador(); break;
            case 6: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion no valida." << endl; break;
        }
    } while (opcion != 6);
    system("cls");
}

void menuCitas() {
    int opcion;
    do {
        cout << "\nGESTION DE CITAS" << endl;
        cout << "1. Crear Cita" << endl;
        cout << "2. Mostrar Citas" << endl;
        cout << "3. Editar Cita" << endl;
        cout << "4. Buscar Cita" << endl;
        cout << "5. Eliminar Cita" << endl;
        cout << "6. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1: CrearCita(); break;
            case 2: LeerCita(); break;
            case 3: EditarCita(); break;
            case 4: BuscarCita(); break;
            case 5: EliminarCita(); break;
            case 6: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion no valida." << endl; break;
        }
    } while (opcion != 6);
    system("cls");
}


int main() {
    int opcion;
    do {
        cout << "Bienvenidos" << endl;
        cout << "Seleccione la opcion a realizar: " << endl;
        cout << "1. Clientes" << endl;
        cout << "2. Vehiculos" << endl;
        cout << "3. Trabajadores" << endl;
        cout << "4. Citas" << endl;
        cout << "5. Cerrar Programa" << endl;
        cin >> opcion;
        switch (opcion) {
            case 1: menuClientes(); break;
            case 2: menuVehiculos(); break;
            case 3: menuTrabajadores(); break;
            case 4: menuCitas(); break;
            case 5: cout << "Saliendo del programa." << endl; break;
            default: cout << "Opcion no valida." << endl; break;
        }
    } while (opcion != 5);
    return 0;
}
