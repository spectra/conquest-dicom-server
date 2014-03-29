CGI Interface
-------------
The main software can act as a CGI behind a webserver and it's the only
"friendly" interface provided in GNU/Linux version (Windows version has a
GUI).  It still can be used as such, but you'll have to copy/move the binary
to the proper place yourself. This package only provides it as a DICOM server
out-of-the-box.

I recommend against running it as a CGI interface since it is not very
secure. If anytime in the future I (or upstream) am able to patch the
obvious vulnerabilities, I will prepare the package to act as a CGI interface
as well, but that is just not the case righ now.


