#ifndef HUMBLENET_P2P_H
#define HUMBLENET_P2P_H

#include "humblenet.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* Is the peer-to-peer network supported on this platform.
*/
HUMBLENET_API ha_bool humblenet_p2p_supported();
	
/*
* Initialize the peer-to-peer library.
*/
HUMBLENET_API int humblenet_p2p_init( const char* server, const char* auth_token, const char* client_token, const char* client_secret );

/*
 * Check if a master signaling server address exists
 */
HUMBLENET_API ha_bool humblenet_p2p_has_server();
	
	
/*
 * Set master signaling server address
 */
HUMBLENET_API void humblenet_p2p_set_server(const char *url);

	
/*
 * Get master signaling server address
 * Pointer exists until library is closed or
 * humblenet_p2p_set_server or humblenet_p2p_get_server is called
 */
HUMBLENET_API const char *humblenet_p2p_get_server();
	
	
/*
 * Connect to master signaling server
 * Assumes server address has been specified
 * Returns true if connection succeeds, false otherwise
 */
HUMBLENET_API ha_bool humblenet_p2p_connect_server();
	
	
/*
 * Returns true if peer authentication info has been set externally (eg. by webpage)
 */
HUMBLENET_API ha_bool humblenet_p2p_has_auth();
	
	
/*
 * Set peer authentication token
 */
HUMBLENET_API void humblenet_p2p_set_auth(const char *authtoken);

/*
* Is the peer-to-peer network supported on this platform.
*/
HUMBLENET_API ha_bool humblenet_p2p_is_initialized();
	
/*
* Shut down the networking library
*/
HUMBLENET_API void humblenet_p2p_shutdown();

/*
* Get the current peer ID of this client
* returns 0 if not yet connected
*/
HUMBLENET_API PeerId humblenet_p2p_get_my_peer_id();
	
/*
* Publish the name of this peer so it can be found by name
*/
HUMBLENET_API int humblenet_p2p_publish_name( const char* name );
	
/*
* Find the PeerId of a named peer (registered on the server)
*/
HUMBLENET_API PeerId humblenet_p2p_lookup_peer_by_name( const char* name );
	
/*
* Send a message to a peer.
*/
HUMBLENET_API int humblenet_p2p_sendto( const void* message, uint32_t length, PeerId topeer, uint8_t nChannel );

/*
* Test if a message is available on the specified channel. 
*/
HUMBLENET_API ha_bool humblenet_p2p_select( uint32_t* length, uint8_t nChannel );
	
/*
* Receive a message sent from a peer
*/
HUMBLENET_API int humblenet_p2p_recvfrom( void* buffer, uint32_t length, PeerId* frompeer, uint8_t nChannel );

/*
* Disconnect a peer
*/
HUMBLENET_API int humblenet_p2p_disconnect( PeerId peer );
	
/*
* Give the p2p system a chance to process whatever it needs to
*/
HUMBLENET_API void humblenet_p2p_update();
	
    
#ifdef __cplusplus
}
#endif

#endif
