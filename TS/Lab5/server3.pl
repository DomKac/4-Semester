#!usr/bin/perl
use HTTP::Daemon;
use HTTP::Status;  
#use IO::File;

# Serwer, który chce powiązać się z określonym adresem na ustalonym porcie HTTP, zostanie skonstruowany w następujący sposób:
my $d = HTTP::Daemon->new( # konstruktor serwera
           LocalAddr => 'localhost', # adres ip komputera lokalnego (127.0.0.1)
           LocalPort => 4320, # wolny port
       ) || die; # zatrzymujemy skrypt

print "Please contact me at: <URL:", $d->url, ">\n";

# d = serwer 
# c = klient
# r = request = żądanie

while (my $c = $d->accept) { # Prawda kiedy połacznie z klientem jest dostępne. 
    while (my $r = $c->get_request) { # Pobieramy żądania od klienta (naszej strony)
        # Pobieramy atrybut metody i sprawdzamy czy jest równy stringowi GET (inne możliwe atrybuty to HEAD, PUT, PATCH lub POST)
        if ($r->method eq 'GET') { 
            
            $file_s = "./strony/index.html";    # index.html - jakis istniejacy plik
            $c->send_file_response($file_s);    # wysyłamy odpowiedź do klienta
        }
        else {
            $c->send_error(RC_FORBIDDEN)        
        }
    }
    $c->close; # zamykamy klienta 
    undef($c); # "oddefinujemy klienta"
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
