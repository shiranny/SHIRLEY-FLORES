// BDSQLEXPRESS.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include<windows.h>
#include<sql.h>
#include<sqlext.h>
#include<iostream>

using namespace std;

int main() {
	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLRETURN ret;
	SQLHSTMT hStmt;


	// Allocate an environment handle
	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

	// Allocate a connection handle
	ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

	// connect to the database
	ret = SQLConnect(hDbc, (SQLWCHAR*)L"sqlexpress", SQL_NTS, (SQLWCHAR*)L"username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		cout << "Connected to database seccessfully." << endl;

		SQLHSTMT hStmt;
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt); 
		 // Example of executing a query 
	
		 // Example SELECT query
		ret = SQLExecDirect(hStmt, (SQLWCHAR*)L" SELECT * FROM Datos_empleados", SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			
			SQLCHAR Nombre[50];
			SQLCHAR Apellido_paterno[40];
			SQLCHAR Apellido_materno[40];
			SQLCHAR Fecha_de_nacimiento[40];
			SQLCHAR RFC[15];
			SQLCHAR Centro_trabajo[40];
			SQLCHAR Puesto[15];
			SQLCHAR Descripcion_del_puesto[40];
			int Numero_empleado;
			cout << "+------------------------------------------------------------------------------------------------------------------------------+" << endl;
			cout << "| No. empleado  |Nombre: | apellido paterno :  | apellido materno: | fecha:  | RFC: | Centro: | Puesto: | Descripcion de puesto:" << endl;
			cout << "+------------------------------------------------------------------------------------------------------------------------------+" << endl;   	
			while (SQLFetch(hStmt) == SQL_SUCCESS) {
				SQLGetData(hStmt, 1, SQL_C_LONG, &Numero_empleado, 0, NULL);
				SQLGetData(hStmt, 2, SQL_C_CHAR, Nombre, sizeof(Nombre), NULL);
				SQLGetData(hStmt, 3, SQL_C_CHAR, Apellido_paterno, sizeof(Apellido_paterno), NULL);
				SQLGetData(hStmt, 4, SQL_C_CHAR, Apellido_materno, sizeof(Apellido_materno), NULL);
				SQLGetData(hStmt, 5, SQL_C_CHAR, Fecha_de_nacimiento, sizeof(Fecha_de_nacimiento), NULL);
				SQLGetData(hStmt, 6, SQL_C_CHAR, RFC, sizeof(RFC), NULL);
				SQLGetData(hStmt, 7, SQL_C_CHAR, Centro_trabajo, sizeof(Centro_trabajo), NULL);
				SQLGetData(hStmt, 8, SQL_C_CHAR, Puesto, sizeof(Puesto), NULL);
				SQLGetData(hStmt, 9, SQL_C_CHAR, Descripcion_del_puesto, sizeof(Descripcion_del_puesto), NULL);
				
				cout << "|" << Numero_empleado << "|  " << Numero << Nombre << " " << Apellido_paterno << " " << Apellido_materno << " " << Fecha_de_nacimiento << " " << RFC << " " << Centro_trabajo << " " << Puesto << " " << Descripcion_del_puesto << "| " endl;
				cout << "+---------------------------------+" endl;
									
			}
		}

		// Free statement handle
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	}
	else {
		cout << "Failed to connect to database." << endl;

	}
	// Disconnect and free handles
	SQLDisconnect(hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return 0;


}