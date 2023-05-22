#!usr/bin/perl
use HTTP::Daemon;
use HTTP::Status;  
#use IO::File;

my $d = HTTP::Daemon->new(
           LocalAddr => 'localhost',
           LocalPort => 4323,
       ) || die;

print "Please contact me at: <URL:", $d->url, ">\n";


my $dir = "./strony"; # katalog ze wszystkimi stronami
my $file_s;
while (my $c = $d->accept) {
    while (my $r = $c->get_request) {
        if ($r->method eq 'GET') {

            # patrzymy czy znajdujemy się na stronie głównej = adres ma postać http://127.0.0.1:4323/
            if($r->uri eq "/" | $r->uri eq "/favicon.ico") {
            # if($r->uri eq "/") {
                $file_s = "./strony/glowna.html";
                $c->send_file_response($file_s);

            } else { # znajdujemy się na którejś z podstron = adres ma postać http://127.0.0.1:4323/strona(X).html
                
                $file_s = $dir.$r->uri;
                $c->send_file_response($file_s);
            }
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
# To samo co IO::Socket::accept, ale zwróci referencję HTTP::Daemon::ClientConn. Zwróci undef, jeśli określiłeś limit czasu i w tym czasie nie zostanie nawiązane żadne połączenie.

# $c->get_request
# Will read data from the client and turn it into a HTTP::Request object which is then returned. Will return undef if reading of the request failed. If it fails, then the HTTP::Daemon::ClientConn object ($c) should be discarded.

# The $c->get_request method support HTTP/1.1 content bodies, including chunked transfer encoding with footer and multipart/* types.

# $c->send_response( [$res] )
# Takes a HTTP::Response object as parameter and send it back to the client as the response.

# $c->send_error( [$code, [$error_message]] )
# Send an error response back to the client. If the $code is missing a ``Bad Request'' error is reported. The $error_message is a string that is incorporated in the body of the HTML entity body.
