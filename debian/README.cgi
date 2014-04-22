CGI Interface
-------------
The main software can act as a CGI behind a webserver and it's the only
"friendly" interface provided in GNU/Linux version (Windows version has a
GUI). For the browser-embedded viewer part it requires an ActiveX-enabled
browser and ships with code I can't really understand, so I've left the CGI
packaging as a wishlist item. This package only provides it as a DICOM server
out-of-the-box.

The dgate binary shipped with this package can still be used as CGI, but
you'll have to copy/move the binary to the proper place yourself. If you have
a CGI-capable webserver installed on the same machine as ConQuest, it's as
easy as:

	bash# ln -s /usr/bin/dgate /usr/lib/cgi-bin

Then you can point your browser to:

	http://localhost/cgi-bin/dgate?port=11112&address=127.0.0.1

But please note that the embedded viewer will not work. You'll be able to
browse studies and view thumbs and individual images, but nothing compared to
a DICOM viewer.
