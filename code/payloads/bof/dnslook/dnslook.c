/***********************************************************************************************************************
*   MODULO:        dnslook.c                                                                                           *
*   DESCRIPCION:   Consulta el nombre DNS del equipo o el sufijo DNS mediante una importacion BOF de KERNEL32.         *
***********************************************************************************************************************/

#include <windows.h>
#include "beacon.h"

/***********************************************************************************************************************
*                                                IMPORTACIONES                                                     *
***********************************************************************************************************************/

DECLSPEC_IMPORT BOOL WINAPI KERNEL32$GetComputerNameExA( COMPUTER_NAME_FORMAT type, LPSTR buffer, LPDWORD size );

/***********************************************************************************************************************
*   FUNCION:       go                                                                                                    *                              *
***********************************************************************************************************************/

VOID	go( PCHAR pArgs, INT iArgumentLength )
{
	datap	stParser;
	INT		iMode		= 0;
	CHAR	szName[256]	= { 0 };
	DWORD	dwNameLength	= sizeof( szName );

	if ( pArgs == NULL || iArgumentLength <= 0 )
	{
		BeaconPrintf( CALLBACK_ERROR, "[!] Falta el argumento" );
		return;
	}

	BeaconDataParse( &stParser, pArgs, iArgumentLength );

	if ( BeaconDataLength( &stParser ) < (INT)sizeof( iMode ) )
	{
		BeaconPrintf( CALLBACK_ERROR, "[!] Argumento incompleto" );
		return;
	}

	iMode = BeaconDataInt( &stParser ); /* 0: hostname; 1: sufijo DNS */

	if ( iMode != 0 && iMode != 1 )
	{
		BeaconPrintf( CALLBACK_ERROR, "[!] Use 0 (host) o 1 (domain)" );
		return;
	}

	if ( !KERNEL32$GetComputerNameExA( iMode ? ComputerNameDnsDomain : ComputerNameDnsHostname, szName, &dwNameLength ) )
	{
		BeaconPrintf( CALLBACK_ERROR, "[-] GetComputerNameExA fallo" );
		return;
	}

	BeaconPrintf( CALLBACK_OUTPUT, "[+] %s: %s", iMode ? "Sufijo DNS" : "Nombre DNS", dwNameLength ? szName : "(vacio)" );
}
