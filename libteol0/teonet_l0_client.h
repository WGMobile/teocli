/** 
 * \file   teonet_l0_client.h
 * \author Kirill Scherba <kirill@scherba.ru>
 * 
 * Created on October 12, 2015, 12:32 PM
 */

/**
 * @mainpage Teocli library Documentation  
 * 
 * * [Native library structures and functions](teonet__l0__client_8h.html) 
 * * [C++ teocli class wrapper](classteocli.html)  
 * * [Basic example](main_8c-example.html)    
 */

#ifndef TEONET_L0_CLIENT_H
#define	TEONET_L0_CLIENT_H

#include <stdint.h>

#if defined(HAVE_MINGW) || defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#endif

#if !defined(HAVE_MINGW) && (defined(_WIN32) || defined(_WIN64))
	#ifdef MS_WIN64
	typedef __int64 ssize_t;
	#else
	typedef _W64 int ssize_t;
	#endif
#endif

/**
 * L0 System commands
 */
enum CMD_L {
    
    CMD_L_ECHO = 65,    ///< Echo command
    CMD_L_ECHO_ANSWER,  ///< Answer to echo command
    CMD_L_PEERS = 72,   ///< Get peers command
    CMD_L_PEERS_ANSWER  ///< Answer to get peers command
            
};

#define L0_BUFFER_SIZE 2048

/**
 * L0 client events
 */
typedef enum teoLNullEvents {
    
    EV_L_CONNECTED,
    EV_L_DISCONNECTED,
    EV_L_RECEIVED
            
} teoLNullEvents;

typedef void (*teoLNullEventsCb)(void *kc, teoLNullEvents event, void *data, 
            size_t data_len, void *user_data) ;

/**
 * L0 client connect data
 */
typedef struct teoLNullConnectData {

    #if defined(HAVE_MINGW) || defined(_WIN32) || defined(_WIN64)
    SOCKET fd;                  ///< Connection socket
    #else
    int fd;                     ///< Connection socket
    #endif
    
    void *read_buffer;          ///< Pointer to saved buffer
    size_t read_buffer_ptr;     ///< Pointer in read buffer
    size_t read_buffer_size;    ///< Read buffer size
    size_t last_packet_ptr;     ///< Last recived packet pointer (length)
    
    teoLNullEventsCb event_cb;  ///< Event callback function
    void *user_data;            ///< User data

} teoLNullConnectData;
        
/**
 * L0 client packet data structure
 * 
 */        
typedef struct teoLNullCPacket {

    uint8_t cmd; ///< Command
    uint8_t peer_name_length; ///< To peer name length (include leading zero)
    uint16_t data_length; ///< Packet data length
    uint8_t reserved_1; ///< Reserved 1
    uint8_t reserved_2; ///< Reserved 2
    uint8_t checksum; ///< Whole checksum
    uint8_t header_checksum; ///< Header checksum
    char peer_name[]; ///< To/From peer name (include leading zero) + packet data

} teoLNullCPacket;

/**
 * KSNet ARP table data structure
 */
typedef struct ksnet_arp_data {

    int16_t mode;       ///< Peers mode: -1 - This host, -2 undefined host, 0 - peer , 1 - r-host, 2 - TCP Proxy peer
    char addr[40];      ///< Peer IP address
    int16_t port;       ///< Peer port

    double last_acrivity;           ///< Last time receved data from peer
    double last_triptime_send;      ///< Last time when triptime request send
    double last_triptime_got;       ///< Last time when triptime received

    double last_triptime;           ///< Last triptime
    double triptime;                ///< Middle triptime

    double monitor_time;            ///< Monitor ping time

} ksnet_arp_data;

/**
 * KSNet ARP table whole data array
 */
typedef struct ksnet_arp_data_ar {
    
    uint32_t length;
    struct _arp_data {
        
        char name[40];
        ksnet_arp_data data;
        
    } arp_data[];
    
} ksnet_arp_data_ar;

#ifdef _WINDLL
#define TEOCLI_API __declspec(dllexport)
#else
#define TEOCLI_API 
#endif

#ifdef	__cplusplus
extern "C" {
#endif
    
/**
 * Get output buffer size
 * @param peer_length
 * @param data_length
 */
#define teoLNullBufferSize(peer_length, data_length) \
    ( sizeof(teoLNullCPacket) + peer_length + data_length )
    
#if (defined(_WIN32) || defined(_WIN64)) && !defined(HAVE_MINGW)   
    #define teoLNullSleep(ms) Sleep(mv)
#else
    #define teoLNullSleep(ms) usleep(ms * 1000)    
#endif
    
    
// Hight level functions    
TEOCLI_API void teoLNullInit();
TEOCLI_API void teoLNullCleanup();

TEOCLI_API teoLNullConnectData *teoLNullConnect(const char *server, int port);
TEOCLI_API teoLNullConnectData* teoLNullConnectE(const char *server, int port, 
        teoLNullEventsCb event_cb, void *user_data);
TEOCLI_API void teoLNullDisconnect(teoLNullConnectData *con);

TEOCLI_API ssize_t teoLNullLogin(teoLNullConnectData *con, const char* host_name);
TEOCLI_API ssize_t teoLNullSend(teoLNullConnectData *con, int cmd, 
        const char *peer_name, void *data, size_t data_length);
TEOCLI_API ssize_t teoLNullRecv(teoLNullConnectData *con);
TEOCLI_API int teoLNullReadEventLoop(teoLNullConnectData *con, int timeout);


// Low level functions
size_t teoLNullPacketCreateLogin(void* buffer, size_t buffer_length,
        const char* host_name);
size_t teoLNullPacketCreate(void* buffer, size_t buffer_length, uint8_t command,
        const char * peer, const void* data, size_t data_length);

ssize_t teoLNullPacketSend(int fd, void* pkg, size_t pkg_length);
ssize_t teoLNullPacketRecv(int fd, void* buf, size_t buf_length);

ssize_t teoLNullPacketSplit(teoLNullConnectData *con, void* data,
        size_t data_len, ssize_t received);

uint8_t get_byte_checksum(void *data, size_t data_length);

#ifdef	__cplusplus
}
#endif

#endif	/* TEONET_L0_CLIENT_H */
