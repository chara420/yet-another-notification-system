#include <a_samp>
#include <S_.w's Includes\ch_notifi.inc>//Cambiar esta direción.
#include <zcmd>
#include <sscanf>
CMD:notifi(playerid, params[])
{
	new footer[25], body[156], time, color;
	if(sscanf(params, "s[25]s[156]ii", footer, body, time, color)) return SendClientMessage(playerid, -1, "/notifi [Footer] [Body] [Tiempo - s] [Color 0 - 1 - 2 - 3 ]");
	switch(color)
	{
		case 0:
		{
			ShowPlayerNotification(playerid, footer, body, time, NOTIFICATION_BLACK);
		}
		case 1:
		{
			ShowPlayerNotification(playerid, footer, body, time, NOTIFICATION_YELLOW);
		}
		case 2:
		{
			ShowPlayerNotification(playerid, footer, body, time, NOTIFICACION_RED);
		}
		case 3:
		{
			ShowPlayerNotification(playerid, footer, body, time, NOTIFICATION_GREEN);
		}
		default: SendClientMessage(playerid, -1, "/notifi [Footer] [Body] [Tiempo - s] [Color 0 - 1 - 2 - 3 ]");
	}
	return 1;
}
public OnPlayerConnect(playerid)
{
	ShowPlayerNotification(playerid, "Bienvenida", "Bienvenido/a a mi servidor de pruebas!.", 100,	NOTIFICATION_GREEN);	
}