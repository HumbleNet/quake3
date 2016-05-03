#ifndef HUMBLENET_H
#define HUMBLENET_H


#include <stddef.h>
#include <stdint.h>

#ifdef HUMBLENET_STATIC
	#define HUMBLENET_DLL_EXPORT
#else
	#ifdef WIN32
		#ifdef HUMBLENET_DLL_BUILD
			#define HUMBLENET_DLL_EXPORT __declspec(dllexport)
		#else
			#define HUMBLENET_DLL_EXPORT __declspec(dllimport)
		#endif
	#else // GCC
		#if defined(__GNUC__) && __GNUC__ >= 4
		# define HUMBLENET_DLL_EXPORT __attribute__ ((visibility("default")))
		#else
		# define HUMBLENET_DLL_EXPORT
		#endif
	#endif
#endif

#define HUMBLENET_API HUMBLENET_DLL_EXPORT


#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t ha_bool;
typedef uint32_t PeerId;
typedef uint32_t LobbyId;
typedef uint32_t GameId;


typedef enum LobbyStatus {
	HUMBLENET_LOBBY_CREATED
	, HUMBLENET_LOBBY_WAITING_RESPONSE
	, HUMBLENET_LOBBY_ESTABLISHED
	, HUMBLENET_LOBBY_ERROR
	, HUMBLENET_LOBBY_CLOSED
} LobbyStatus;


typedef enum LobbyError {
	HUMBLENET_LOBBY_ERROR_NO_SUCH_LOBBY
	, HUMBLENET_LOBBY_ERROR_ALREADY_JOINED
	, HUMBLENET_LOBBY_ERROR_LOBBY_FULL
	, HUMBLENET_LOBBY_ERROR_WRONG_PASSWORD
} LobbyError;


/*
 * If using threads, you must lock before any calls to the humblent_apis.
 */
HUMBLENET_API void humblenet_lock();

/*
 * If using threads, you must unlock when done with any calls to the humblent_apis.
 */
HUMBLENET_API void humblenet_unlock();
    
/*
 * Allow network polling to occur. This is already thread safe and must NOT be within a lock/unlock block
 */
HUMBLENET_API void humblenet_poll(int ms);
    
/*
 * Get error string
 * Return value will stay valid until next call to humblenet_set_error
 * or humblenet_clear_error() is called
 */
HUMBLENET_API const char *humblenet_get_error();


/*
 * Set error string
 * Parameter is copied to private storage
 * Must not be NULL
 */
HUMBLENET_API void humblenet_set_error(const char *error);


/*
 * Clear error string
 */
HUMBLENET_API void humblenet_clear_error();


#ifdef __cplusplus
}
#endif


#endif // HUMBLENET_H
