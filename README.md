# packet-sniffer
Packet sniffing experimentation.

Tested on Ubuntu 17.10 and Windows 10. 

This uses raw sockets and these come with limitations in Windows, most notably: 

* The network (IP) layer is the lowest protocol level which can be captured.  Link (Ethernet) is available on *nix.
* Incoming TCP packets are not visible (but they are on *nix)

I could have used libcap (and Winpcap) and get around these limitations however this is a hobby project and I wanted to explore raw sockets on both platforms.