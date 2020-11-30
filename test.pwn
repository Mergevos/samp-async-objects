#include <a_samp>

#include <YSI_Visual\y_commands>
#define PP_SYNTAX_AWAIT
#include <PawnPlus>
#include "async-objects"

main() 
{
    return ;
}

public OnGameModeInit()
{
    CreateObject(2921,134.9397,-72.9322,1.4297, 0, 0,0);
  
    return 1;
}


YCMD:test(playerid, params[], help)
{ 
    if(help) {
        return 0;
    }
    SelectObject(playerid);

    return 1;
}

public OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
{
    new obj_res[e_OBJECT_INFO];
    await_arr(obj_res) AsyncObject_Edit(playerid, objectid);
    print("Response awaited");
    if(obj_res[E_OBJECT_Response] == EDIT_RESPONSE_FINAL) {
        print("Response final, player clicked on save icon.");
    } else if(obj_res[E_OBJECT_Response] == EDIT_RESPONSE_CANCEL) {
        print("Canceled");
    }
    return 1;
}

public OnPlayerEditObject(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ )
{
    return 1;
}