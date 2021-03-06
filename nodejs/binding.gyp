{
   "targets": [
    {
        "target_name": 'teonet_client',
        "sources": [ "src/teo_main.cpp",
                     "src/connector.cpp",
		     "src/errno_exeption.cpp",
		     "src/teo_exeption.cpp",
		     "src/teo_packet.cpp",
                     "src/libteol0/teonet_l0_client.c" ],
        "include_dirs": [
	"<!(node -e \"require('nan')\")",
        ],
        'link_settings': {
    	    'libraries': []
        },
	"cflags_cc": [
    	    "-std=c++11"
        ],
	"ldflags": [
	    "-g"
	]
    }
   ]
}
