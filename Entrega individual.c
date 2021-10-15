#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
//#include <my_global.h>

int main (int argc, char **argv)
{
	MYSQL *conn;
	int err;
	
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	//Creamos una conexion
	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		printf ("Error al crear la conexion /n: %u %s /n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	//Inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root","mysql","BBDD_JUEGO",0,NULL,0);
	if (conn == NULL)
	{
		printf ("Error al inicialiazr la conexion /n: %u %s", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	//Consulta SQL
	err = mysql_query (conn, "SELECT COUNT(ID) FROM (Jugador,Partida) WHERE NOMBRE = 'Juan'");
	if (err != 0)
	{
		printf ("Error al consultar datos de la base %u %s /n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	//Recogemos el resultado de la consulta.
	resultado = mysql_store_result(conn);
	
	row = mysql_fetch_row(resultado);
	if (row == NULL)
	{
		printf ("No se han obtenido datos en la consulta /n");
	}
	else
	{
		int jugadas = atoi(row[0]);
		printf ("Juan ha jugado %d partidas \n", jugadas);
	}
	
	//Cerrar la conexion
	mysql_close(conn);
	exit(0);
}


