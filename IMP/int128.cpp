#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef __int128 ell;

std::ostream&
operator<<( std::ostream& dest, __int128_t value ) {
	std::ostream::sentry s( dest );
	if ( s ) {
		__uint128_t tmp = value < 0 ? -value : value; char buffer[ 128 ];
		char* d = std::end( buffer );
		do {	-- d; *d = "0123456789"[ tmp % 10 ]; tmp /= 10;} while ( tmp != 0 );
		if ( value < 0 ) {-- d; *d = '-';}
		int len = std::end( buffer ) - d;
		if ( dest.rdbuf()->sputn( d, len ) != len ) {dest.setstate( std::ios_base::badbit );}
	}
	return dest;
}

__int128 read() {
	__int128 x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ell a,b;
    a=read();
    b=read();
    cout<<a+b;

    return 0;
}

