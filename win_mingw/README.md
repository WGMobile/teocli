Install MinGW-64 under Ubuntu:

    sudo apt-get install mingw-w64

To make this application and library under Linux use command line:

    ./make_exe.sh

To run "teocli" application use command line:

    teocli.exe C5 10.12.35.53 9000 teostream "Hello world!"

where:

    C5 - client name
    10.12.35.53 - IP address of L0 Teonet server to connect to
    9000 - servers port
    teostream - name of teonet application to send message to
    "Hello world!" - message to send

Call from Internet:

    ./teocli C5 gt1.kekalan.net 9010 ps-server Hello
    ./teocli C5 gt1.kekalan.net 9010 teo-gbs Hello
    ./teocli C5 gt1.kekalan.net 9010 teonet-11 Hello
    ./teocli C5 gt1.kekalan.net 9010 teonet-17 Hello

