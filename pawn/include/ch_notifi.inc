////v0.2
#include <YSI\y_hooks>
#include <strlib>
//config
//internal vars & defines
#define 	NOTIFICATION_BLACK 0
#define 	NOTIFICATION_YELLOW 1
#define		NOTIFICACION_RED 2
#define 	NOTIFICATION_GREEN 3

//#define 	DEBUG_MODE
#define		segundos(%0) 		(1000 * %0)
static
 			PlayerText:base_box[MAX_PLAYERS],
	   		PlayerText:box_fotter[MAX_PLAYERS],
	   		PlayerText:icon[MAX_PLAYERS],
	   		PlayerText:text_fotter[MAX_PLAYERS],
	   		PlayerText:text_box[MAX_PLAYERS];
static 		
			bool:UsedNotifi[MAX_PLAYERS],
			Timer_Clossed[MAX_PLAYERS];
enum
{
	BOX_BLACK			=	0x00000062,
	BOX_FOTTER_BLACK	=	0x0000009A,
	//
	BOX_YELLOW 			=	0xFFFF006A,
	BOX_FOTTER_YELLOW 	=	0xFFFF00B7,
	//
	BOX_RED				=	0xFF00007A,
	BOX_FOTTER_RED		=	0xFF00009A,
	//
	BOX_GREEN			=	0x00FF0073,
	BOX_FOTTER_GREEN	=	0x00FF00B0,
}
#define ICON_BLACK			"LD_CHAT:goodcha"
#define ICON_YELLOW			"LD_CHAT:badchat"
#define ICON_RED			"LD_CHAT:thumbdn"
#define ICON_GREEN			"LD_CHAT:thumbup"
//funcs
stock ShowPlayerNotification(playerid, textfotter[], text[], time = 3, style = NOTIFICATION_BLACK)
{
	new len = strlen(text);
	new result[512];
	new j = 0;
	new count = 0;
	for (new i = 0; i < len; i++)
	{
    	result[j++] = text[i];
    	count++;
    	if (count == 23)
    	{
        	strcat(result, "~n~");
        	j += 3;
        	count = 0;
    	}
    	if (count == 46)
    	{
        	strcat(result, "~n~");
        	j += 3;
        	count = 0;
    	}
    	if (count == 69)
    	{
        	strcat(result, "~n~");
        	j += 3;
        	count = 0; 
    	}
    	if (count == 92)
    	{
        	strcat(result, "~n~");
        	j += 3;
        	count = 0; 
    	}
	}
	/*
	new len = strlen(text);
	new result[512]; // crear nueva cadena con espacio suficiente
	new j = 0;
	for (new i = 0; i < len; i++)
	{
    	result[j++] = text[i]; // copiar el carácter de la cadena original al resultado
    	if ((i - 22) % 26 == 0 && i >= 22) // verificar si es un índice de salto de línea
    	{
        	strcat(result, "~n~"); // agregar los caracteres de salto de línea al resultado
        	j += 3; // ajustar el índice j para la próxima copia de carácter
    	}
	}*/
	PlayerTextDrawSetString(playerid, text_box[playerid], result);
	PlayerTextDrawShow(playerid, text_box[playerid]);

	PlayerTextDrawSetString(playerid, text_fotter[playerid], textfotter);
	PlayerTextDrawShow(playerid, text_fotter[playerid]);

	Timer_Clossed[playerid] = SetTimerEx("CloseTD", segundos(time), false,"i",playerid);
	UsedNotifi[playerid] = true;
	switch(style)
	{
		case NOTIFICATION_BLACK:
		{
			PlayerTextDrawBoxColor(playerid, base_box[playerid], BOX_BLACK);
			PlayerTextDrawBoxColor(playerid, box_fotter[playerid], BOX_FOTTER_BLACK);
			PlayerTextDrawSetString(playerid, icon[playerid], ICON_BLACK);
			PlayerTextDrawBoxColor(playerid, icon[playerid], BOX_FOTTER_BLACK);

			PlayerTextDrawShow(playerid, base_box[playerid]);
			PlayerTextDrawShow(playerid, box_fotter[playerid]);
			PlayerTextDrawShow(playerid, icon[playerid]);
		}
		case NOTIFICATION_YELLOW:
		{
			PlayerTextDrawBoxColor(playerid, base_box[playerid], BOX_YELLOW);
			PlayerTextDrawBoxColor(playerid, box_fotter[playerid], BOX_FOTTER_YELLOW);
			PlayerTextDrawSetString(playerid, icon[playerid], ICON_YELLOW);
			PlayerTextDrawBoxColor(playerid, icon[playerid], BOX_FOTTER_YELLOW);

			PlayerTextDrawShow(playerid, base_box[playerid]);
			PlayerTextDrawShow(playerid, box_fotter[playerid]);
			PlayerTextDrawShow(playerid, icon[playerid]);
		}
		case NOTIFICACION_RED:
		{
			PlayerTextDrawBoxColor(playerid, base_box[playerid], BOX_RED);
			PlayerTextDrawBoxColor(playerid, box_fotter[playerid], BOX_FOTTER_RED);
			PlayerTextDrawSetString(playerid, icon[playerid], ICON_RED);
			PlayerTextDrawBoxColor(playerid, icon[playerid], BOX_FOTTER_RED);

			PlayerTextDrawShow(playerid, base_box[playerid]);
			PlayerTextDrawShow(playerid, box_fotter[playerid]);
			PlayerTextDrawShow(playerid, icon[playerid]);
		}
		case NOTIFICATION_GREEN:
		{
			PlayerTextDrawBoxColor(playerid, base_box[playerid], BOX_GREEN);
			PlayerTextDrawBoxColor(playerid, box_fotter[playerid], BOX_FOTTER_GREEN);
			PlayerTextDrawSetString(playerid, icon[playerid], ICON_GREEN);
			PlayerTextDrawBoxColor(playerid, icon[playerid], BOX_FOTTER_GREEN);

			PlayerTextDrawShow(playerid, base_box[playerid]);
			PlayerTextDrawShow(playerid, box_fotter[playerid]);
			PlayerTextDrawShow(playerid, icon[playerid]);
		}
	}
	return 1;
}
//internal callbacks
forward  CloseTD(playerid);
public CloseTD(playerid)
{
	UsedNotifi[playerid] = false;
	PlayerTextDrawHide(playerid, base_box[playerid]);
	PlayerTextDrawHide(playerid, box_fotter[playerid]);
	PlayerTextDrawHide(playerid, icon[playerid]);
	PlayerTextDrawHide(playerid, text_fotter[playerid]);
	PlayerTextDrawHide(playerid, text_box[playerid]);
	KillTimer(Timer_Clossed[playerid]);
	return 1;
}
hook OnPlayerConnect(playerid)
{
	LoadPlayerTextDraws(playerid);
	return 1;
}
hook OnPlayerDisconnect(playerid, reason)
{
	UnLoadPlayerTextDraws(playerid);
	return 1;
}
//internal funcs
static LoadPlayerTextDraws(playerid)
{
	#if defined DEBUG_MODE
	print("ch_notifi.inc: INTERNAL::LoadPlayerTextDraws called");
	#endif
	base_box[playerid] = CreatePlayerTextDraw(playerid, 157.625000, 247.666595, "base");
	PlayerTextDrawLetterSize(playerid, base_box[playerid], 0.000000, 9.956479);
	PlayerTextDrawTextSize(playerid, base_box[playerid], -6.375000, 0.000000);
	PlayerTextDrawAlignment(playerid, base_box[playerid], 1);
	PlayerTextDrawColor(playerid, base_box[playerid], 0);
	PlayerTextDrawUseBox(playerid, base_box[playerid], true);
	PlayerTextDrawBoxColor(playerid, base_box[playerid], -65430);
	PlayerTextDrawSetShadow(playerid, base_box[playerid], 0);
	PlayerTextDrawSetOutline(playerid, base_box[playerid], 0);
	PlayerTextDrawFont(playerid, base_box[playerid], 0);
	
	box_fotter[playerid] = CreatePlayerTextDraw(playerid, 157.000000, 331.083343, "base_fotter");
	PlayerTextDrawLetterSize(playerid, box_fotter[playerid], 0.000000, 0.720368);
	PlayerTextDrawTextSize(playerid, box_fotter[playerid], -3.250000, 0.000000);
	PlayerTextDrawAlignment(playerid, box_fotter[playerid], 1);
	PlayerTextDrawColor(playerid, box_fotter[playerid], 0);
	PlayerTextDrawUseBox(playerid, box_fotter[playerid], true);
	PlayerTextDrawBoxColor(playerid, box_fotter[playerid], -65353);
	PlayerTextDrawSetShadow(playerid, box_fotter[playerid], 0);
	PlayerTextDrawSetOutline(playerid, box_fotter[playerid], 0);
	PlayerTextDrawFont(playerid, box_fotter[playerid], 0);
	
	icon[playerid] = CreatePlayerTextDraw(playerid, 0.000000, 329.583343, "LD_CHAT:badchat");
	PlayerTextDrawLetterSize(playerid, icon[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, icon[playerid], 16.875000, 10.500000);
	PlayerTextDrawAlignment(playerid, icon[playerid], 1);
	PlayerTextDrawColor(playerid, icon[playerid], -65353);
	PlayerTextDrawSetShadow(playerid, icon[playerid], 0);
	PlayerTextDrawSetOutline(playerid, icon[playerid], 0);
	PlayerTextDrawFont(playerid, icon[playerid], 4);
	
	text_fotter[playerid] = CreatePlayerTextDraw(playerid, 151.875000, 328.999969, "Advertencia");
	PlayerTextDrawLetterSize(playerid, text_fotter[playerid], 0.379374, 1.059999);
	PlayerTextDrawAlignment(playerid, text_fotter[playerid], 3);
	PlayerTextDrawColor(playerid, text_fotter[playerid], -1);
	PlayerTextDrawSetShadow(playerid, text_fotter[playerid], 0);
	PlayerTextDrawSetOutline(playerid, text_fotter[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, text_fotter[playerid], 51);
	PlayerTextDrawFont(playerid, text_fotter[playerid], 2);
	PlayerTextDrawSetProportional(playerid, text_fotter[playerid], 1);
	
	text_box[playerid] = CreatePlayerTextDraw(playerid, 2.500000, 246.166687, "AAAAAAAAAAAAAAAAAAAAA");
	PlayerTextDrawLetterSize(playerid, text_box[playerid], 0.242499, 1.133332);
	PlayerTextDrawAlignment(playerid, text_box[playerid], 1);
	PlayerTextDrawColor(playerid, text_box[playerid], -1);
	PlayerTextDrawSetShadow(playerid, text_box[playerid], 0);
	PlayerTextDrawSetOutline(playerid, text_box[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, text_box[playerid], 51);
	PlayerTextDrawFont(playerid, text_box[playerid], 2);
	PlayerTextDrawSetProportional(playerid, text_box[playerid], 1);
}
static UnLoadPlayerTextDraws(playerid)
{
	#if defined DEBUG_MODE
	print("ch_notifi.inc: INTERNAL::UnLoadPlayerTextDraws called");
	#endif
	UsedNotifi[playerid] = false;
	KillTimer(Timer_Clossed[playerid]);
	PlayerTextDrawDestroy(playerid, base_box[playerid]);
	PlayerTextDrawDestroy(playerid, box_fotter[playerid]);
	PlayerTextDrawDestroy(playerid, icon[playerid]);
	PlayerTextDrawDestroy(playerid, text_fotter[playerid]);
	PlayerTextDrawDestroy(playerid, text_box[playerid]);
}
hook OnScripInit()
{
	#if defined DEBUG_MODE
	print("ch_notifi.inc INTERNAL:: Loaded!");
	#endif
}