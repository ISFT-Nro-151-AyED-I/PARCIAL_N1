#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

const int MAX_CLIENTES = 100;
const int CODIGO_INICIAL = 100;
const string ARCHIVO_CLIENTES = "Clientes.txt";

typedef struct 
    {
        string codigo;
        string nombre;
        string celular;
        string mail;
    } tCliente;

typedef struct 
    {
        tCliente clientes[MAX_CLIENTES];
        int contador;
    } tListaClientes;


void menu();
void cargarClientes(tListaClientes &lista);
void guardarClientes(const tListaClientes &lista);
void crearCliente(tListaClientes &lista);
void listarClientes(const tListaClientes &lista);
void mostrarCliente(const tListaClientes &lista, const string &codigo);
void actualizarCliente(tListaClientes &lista);
void eliminarCliente(tListaClientes &lista);
int buscarCliente(const tListaClientes &lista, const string &codigo);

int main() 
    {
        menu();
        return 0;
    }

void menu() 
    {
        tListaClientes lista;
        lista.contador = 0;
        
        cargarClientes(lista);
        
        int opcion;

        do 
            {
                cout << "\n\n=====================================\n";
                cout << "SISTEMA DE GESTION DE CLIENTES\n";
                cout << "=====================================\n";
                cout << "1. Crear nuevo cliente\n";
                cout << "2. Listar todos los clientes\n";
                cout << "3. Mostrar un cliente por codigo\n";
                cout << "4. Actualizar datos de cliente\n";
                cout << "5. Eliminar cliente\n";
                cout << "0. Salir\n";
                cout << "=====================================\n";
                cout << "Selecciona una opcion: ";
                cin >> opcion;
                cin.ignore();
                
                switch(opcion) 
                    {
                        case 1:
                            crearCliente(lista);
                            break;
                        case 2:
                            listarClientes(lista);
                            break;
                        case 3: 
                            {
                                string codigo;
                                cout << "\nIngresa el codigo del cliente (ej. C100): ";
                                getline(cin, codigo);

                                mostrarCliente(lista, codigo);
                                break;
                            }
                        case 4:
                            actualizarCliente(lista);
                            break;
                        case 5:
                            eliminarCliente(lista);
                            break;
                        case 0:
                            guardarClientes(lista);
                            cout << "\nDatos guardados. Saliendo...\n";
                            break;
                        default:
                            cout << "\nOpcion no valida. Intenta nuevamente.\n";
                    }
            } while (opcion != 0);
    }

void cargarClientes(tListaClientes &lista) 
    {
        ifstream archivo(ARCHIVO_CLIENTES);
        
        if (archivo.is_open()) 
            {
                lista.contador = 0;
                
                while (lista.contador < MAX_CLIENTES && getline(archivo, lista.clientes[lista.contador].codigo)) 
                    {
                        getline(archivo, lista.clientes[lista.contador].nombre);
                        getline(archivo, lista.clientes[lista.contador].celular);
                        getline(archivo, lista.clientes[lista.contador].mail);
                        lista.contador++;
                    }

                archivo.close();
            }
    }

void guardarClientes(const tListaClientes &lista) 
    {
        ofstream archivo(ARCHIVO_CLIENTES);
        
        if (archivo.is_open()) 
            {
                for (int i = 0; i < lista.contador; i++) 
                    {
                        archivo << lista.clientes[i].codigo << endl;
                        archivo << lista.clientes[i].nombre << endl;
                        archivo << lista.clientes[i].celular << endl;
                        archivo << lista.clientes[i].mail << endl;
                    }
                archivo.close();
            }
    }

void crearCliente(tListaClientes &lista) 
    {
        if (lista.contador < MAX_CLIENTES) 
            {
                tCliente nuevo;
                
                if (lista.contador == 0) 
                    {
                        nuevo.codigo = "C" + to_string(CODIGO_INICIAL);
                    } else 
                        {
                            string ultimoCodigo = lista.clientes[lista.contador-1].codigo.substr(1);
                            int numCodigo = stoi(ultimoCodigo) + 1; 
                            nuevo.codigo = "C" + to_string(numCodigo);
                        }
                
                cout << "\n\nCREAR NUEVO CLIENTE\n";
                cout << "===================\n";
                cout << "Codigo asignado: " << nuevo.codigo << endl;
                cout << "Nombre: ";
                getline(cin, nuevo.nombre);
                cout << "Celular: ";
                getline(cin, nuevo.celular);
                cout << "Email: ";
                getline(cin, nuevo.mail);
                
                lista.clientes[lista.contador] = nuevo;
                lista.contador++;
                
                cout << "\nCliente creado exitosamente.\n";

                guardarClientes(lista);
            } else 
                {
                    cout << "\nNo se pueden agregar mas clientes. Limite alcanzado.\n";
                }
    }

    void listarClientes(const tListaClientes &lista) 
        {
            cout << "\n\nLISTADO DE CLIENTES\n";
            cout << "===================\n";

            if (lista.contador == 0) 
                {
                    cout << "No hay clientes registrados.\n";
                } else 
                    {
                        cout << left << setw(10) << "CODIGO" 
                            << setw(30) << "NOMBRE" 
                            << setw(20) << "CELULAR" 
                            << setw(30) << "EMAIL" << endl;
                        cout << string(90, '-') << endl;
                        
                        for (int i = 0; i < lista.contador; i++) 
                            {
                                cout << left << setw(10) << lista.clientes[i].codigo
                                    << setw(30) << lista.clientes[i].nombre
                                    << setw(20) << lista.clientes[i].celular
                                    << setw(30) << lista.clientes[i].mail << endl;
                            }
                    }
        }

    void mostrarCliente(const tListaClientes &lista, const string &codigo) 
        {
            int pos = buscarCliente(lista, codigo);
            
            if (pos != -1) 
                {
                    cout << "\n\nDATOS DEL CLIENTE\n";
                    cout << "=================\n";
                    cout << "Codigo: " << lista.clientes[pos].codigo << endl;
                    cout << "Nombre: " << lista.clientes[pos].nombre << endl;
                    cout << "Celular: " << lista.clientes[pos].celular << endl;
                    cout << "Email: " << lista.clientes[pos].mail << endl;
                } else 
                    {
                        cout << "\nCliente no encontrado.\n";
                    }
        }

void actualizarCliente(tListaClientes &lista) 
    {
        if (lista.contador == 0) 
            {
                cout << "\nNo hay clientes registrados para actualizar.\n";
                return;
            }
        
        string codigo;
        cout << "Ingresa el codigo del cliente a actualizar (ej. C100): ";
        getline(cin, codigo);
        
        int pos = buscarCliente(lista, codigo);
        
        if (pos == -1) 
            {
                cout << "\nCliente no encontrado.\n";
                return;
            }
        
        cout << "\n\nACTUALIZAR CLIENTE\n";
        cout << "==================\n";
        cout << "Deja en blanco para mantener el valor actual\n";
        
        string temp;
        
        cout << "Nombre actual: " << lista.clientes[pos].nombre << endl;
        cout << "Nuevo nombre: ";
        getline(cin, temp);
        if (!temp.empty()) lista.clientes[pos].nombre = temp;
        
        cout << "Celular actual: " << lista.clientes[pos].celular << endl;
        cout << "Nuevo celular: ";
        getline(cin, temp);
        if (!temp.empty()) lista.clientes[pos].celular = temp;
        
        cout << "Email actual: " << lista.clientes[pos].mail << endl;
        cout << "Nuevo email: ";
        getline(cin, temp);
        if (!temp.empty()) lista.clientes[pos].mail = temp;
        
        guardarClientes(lista);
        cout << "\nDatos del cliente actualizados correctamente.\n";
    }

void eliminarCliente(tListaClientes &lista) 
    {
        if (lista.contador == 0) 
            {
                cout << "\nNo hay clientes registrados para eliminar.\n";
                return;
            }
        
        string codigo;
        cout << "\nIngresa el codigo del cliente a eliminar (ej. C100): ";
        getline(cin, codigo);
        
        int pos = buscarCliente(lista, codigo);
        
        if (pos != -1) 
            {
                cout << "\n\nCLIENTE A ELIMINAR\n";
                cout << "==================\n";

                mostrarCliente(lista, codigo);
                
                char confirmar;

                cout << "\nEsta seguro que desea eliminar este cliente? (s/n): ";
                cin >> confirmar;
                cin.ignore();
                
                if (confirmar == 's' || confirmar == 'S') 
                    {
                        for (int i = pos; i < lista.contador - 1; i++) 
                            {
                                lista.clientes[i] = lista.clientes[i + 1];
                            }
                        lista.contador--;
                        
                        cout << "\nCliente eliminado exitosamente.\n";
                        guardarClientes(lista);
                    } else 
                        {
                            cout << "\nOperacion cancelada.\n";
                        }
            } else 
                {
                    cout << "\nCliente no encontrado.\n";
                }
    }

int buscarCliente(const tListaClientes &lista, const string &codigo) 
    {
        for (int i = 0; i < lista.contador; i++) 
            {
                if (lista.clientes[i].codigo == codigo) 
                    {
                        return i;
                    }
            }
        return -1;
    }