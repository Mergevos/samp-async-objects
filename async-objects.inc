/*
	* Library: Samp Async Objects (async-objects.inc)
	* Author: Mergevos
	* Date: 30. Novembre 2020.
	* Copyright: (C) 2020
	* Credits: 
        IllidanS4 - PawnPlus
        Graber - Snippets from async-dialogs.inc. 
*/

/**
 * <library name="async-objects">
 * <section>
 *  Version
 * </section>
 *  1.0.0
 * </library>
 */

#if defined _inc_async_objects
    #undef _inc_async_objects
#endif

#if defined _Async_Objects_included_
    #endinput
#endif
#define _Async_Objects_included_

#include <a_samp>

#include <PawnPlus>

#define _ASYNC_OBJECT_VERSION "1.0.0"

/* 
 * Enum * 
 */

enum e_OBJECT_INFO
{
	E_OBJECT_Response,
    E_OBJECT_PlayerObject,
    E_OBJECT_fX,
    E_OBJECT_fY,
    E_OBJECT_fZ,
    E_OBJECT_fRotX,
    E_OBJECT_fRotY,
    E_OBJECT_fRotZ
};

static CallbackHandler: AsyncObject_Handler;
static Task:AsyncObject_PlayerTask[MAX_PLAYERS] = {Task:0, ...};

/*
 * Initializers and finalizers *
 */

forward _pp@on_init@PPAsync_Objects();
public _pp@on_init@PPAsync_Objects() {
	wait_ticks(1);
	AsyncObject_Handler = pawn_register_callback("OnPlayerEditObject", "AsyncObjectHandler"); //rewriting callback, took from async_dialogs, by Graber.
    printf("[%s] Async-Objects by Mergevos loaded!", _ASYNC_OBJECT_VERSION);
}

forward _pp@on_exit@PPAsync_Objects();
public _pp@on_exit@PPAsync_Objects() {
	pawn_unregister_callback(AsyncObject_Handler);
    printf("[%s] Async-Objects by Mergevos unloaded!", _ASYNC_OBJECT_VERSION);
}

/* 
 * Wrapper * 
 */

#if defined ASYNC_OBJECT_SYNTAX_EDIT

    /**
     * <summary> Wrapper for AsyncObject_Edit.</summary>
     */
    
    stock Task: EditObjectAsync(playerid, objectid) {
        return AsyncObject_Edit(playerid, objectid);
    }

#endif

/* 
 * APi *
 */

/**
 * <summary> Edits an object asynchronously.</summary>
 * <param name="playerid"> Player who edits object.</param>
 * <param name="objectid"> Object which is being edited.</param>
 * <returns> New task.</returns>
 * <remarks> Uses PawnPlus Tasks to start a new task and then await for its response. Their response/result is set in OnPlayerEdiObject's handler. </remarks>
 */

stock Task: AsyncObject_Edit(playerid, objectid) {
    pawn_call_native("EditObject", "dd", playerid, objectid);
    if(AsyncObject_PlayerTask[playerid]) {
        task_delete(AsyncObject_PlayerTask[playerid]);
    }
    return AsyncObject_PlayerTask[playerid] = task_new();
}

/* 
 * Callback Handlers *
 */

/**
 * AsyncObjectHandler is handler callback for OnPlayerEditObject. It gets called whenever OnPlayerEditObject is called.
 */

forward AsyncObjectHandler(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ );
public AsyncObjectHandler(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ ) {
    new 
        obj_response[e_OBJECT_INFO];

    obj_response[E_OBJECT_Response] = response;
    obj_response[E_OBJECT_PlayerObject] = playerobject;

    if (response == EDIT_RESPONSE_CANCEL || response == EDIT_RESPONSE_FINAL) {
        new 
            const Task:task = AsyncObject_PlayerTask[playerid];

        AsyncObject_PlayerTask[playerid] = Task:0;
        task_set_result_arr(task, obj_response);
    }

    return 1;
}