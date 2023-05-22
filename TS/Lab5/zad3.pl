#!usr/bin/perl

use HTTP::Daemon;
use HTTP::Status;  
#use IO::File;

my $d = HTTP::Daemon->new(
           LocalAddr => 'localhost',
           LocalPort => 4322,
       )|| die;

print "Please contact me at: <URL:", $d->url, ">\n";

while (my $c = $d->accept) {
    while (my $r = $c->get_request) {
        if ($r->method eq 'GET') {
            
            $file_s = "./strony/zad3.html";
            # otwieramy plik do którego wpiszemy nagłówek żądania klienta
            open(FH, '>', $file_s) or die $!; 
            # iterujemy po każdym polu nagłówka
            foreach($r->header_field_names) {
                # wpisujemy do pliku każdy nagłówek wraz z jej wartością
                print FH ($_ . "   ----->   " . $r->header($_) . "<br>" );
            }
            close(FH);
            $c->send_file_response($file_s);
            
        }
        else {
            $c->send_error(RC_FORBIDDEN)
        }
    }
    $c->close;
    undef($c);
}

# $d->url
# Returns a URL string that can be used to access the server root.
# Zwaraca adres URL w stringu którego można użyć w celu uzyskania dostępu do katalogu głównego serwera.

# $c = $d->accept
# Same as IO::Socket::accept but will return an HTTP::Daemon::ClientConn reference. It will return undef if you have specified a timeout and no connection is made within that time.

# $c->get_request
# Will read data from the client and turn it into a HTTP::Request object which is then returned. Will return undef if reading of the request failed. If it fails, then the HTTP::Daemon::ClientConn object ($c) should be discarded.

# The $c->get_request method support HTTP/1.1 content bodies, including chunked transfer encoding with footer and multipart/* types.

# $c->send_response( [$res] )
# Takes a HTTP::Response object as parameter and send it back to the client as the response.

# $c->send_error( [$code, [$error_message]] )
# Send an error response back to the client. If the $code is missing a ``Bad Request'' error is reported. The $error_message is a string that is incorporated in the body of the HTML entity body.
